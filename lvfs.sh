#!/usr/bin/env bash

set -e

BOOTLOADER_VID="03EB"
BOOTLOADER_PID="2FF4"
BOOTLOADER_REV="0000"
BOOTLOADER_ID="USB\VID_${BOOTLOADER_VID}&PID_${BOOTLOADER_PID}&REV_${BOOTLOADER_REV}"
echo "BOOTLOADER_ID: ${BOOTLOADER_ID}"

BOOTLOADER_UUID="$(appstream-util generate-guid "${BOOTLOADER_ID}")"
echo "BOOTLOADER_UUID: ${BOOTLOADER_UUID}"

RUNTIME_VID="1209"
RUNTIME_PID="1776"
RUNTIME_REV="0001"
RUNTIME_ID="USB\VID_${RUNTIME_VID}&PID_${RUNTIME_PID}&REV_${RUNTIME_REV}"
echo "RUNTIME_ID: ${RUNTIME_ID}"

RUNTIME_UUID="$(appstream-util generate-guid "${RUNTIME_ID}")"
echo "RUNTIME_UUID: ${RUNTIME_UUID}"

#TODO: Should --dirty be used?
REVISION="$(git describe --tags)"
echo "REVISION: ${REVISION}"

DATE="$(git show -s --format="%ci" "$REVISION" | cut -d " " -f 1)"
echo "DATE: ${DATE}"

if [ -z "$1" ]
then
    echo "$0 [description]" >&2
    exit 1
fi
DESCRIPTION="$1"
echo "DESCRIPTION: ${DESCRIPTION}"

NAME="thelio-io_${REVISION}"
echo "NAME: ${NAME}"

SOURCE="https://github.com/system76/thelio-io-firmware/releases/tag/${REVISION}"
echo "SOURCE: ${SOURCE}"

BUILD="build/lvfs/${NAME}"
echo "BUILD: ${BUILD}"

rm -rf "${BUILD}"
mkdir -pv "${BUILD}"

make "build/atmega32u4/main.bin"
dfu-tool convert dfu "build/atmega32u4/main.bin" "${BUILD}/firmware.dfu"
dfu-tool set-vendor "${BUILD}/firmware.dfu" "0x${BOOTLOADER_VID}"
dfu-tool set-product "${BUILD}/firmware.dfu" "0x${BOOTLOADER_PID}"
dfu-tool set-release "${BUILD}/firmware.dfu" "0x${BOOTLOADER_REV}"
dfu-tool dump "${BUILD}/firmware.dfu"

echo "writing '${BUILD}/firmware.metainfo.xml'"
cat > "${BUILD}/firmware.metainfo.xml" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!-- Copyright 2019 System76 <info@system76.com> -->
<component type="firmware">
  <id>com.system76.ThelioIo.firmware</id>
  <name>Thelio Io</name>
  <summary>Firmware for the System76 Thelio Io</summary>
  <description>
    <p>
      The System76 Thelio Io firmware provides fan and power button control
      for System76 Thelio systems. There is additional drive backplane
      functionality that is not controlled by firmware.
    </p>
  </description>
  <provides>
    <!-- ${BOOTLOADER_ID} -->
    <firmware type="flashed">${BOOTLOADER_UUID}</firmware>
    <!-- ${RUNTIME_ID} -->
    <firmware type="flashed">${RUNTIME_UUID}</firmware>
  </provides>
  <url type="homepage">https://github.com/system76/thelio-io</url>
  <metadata_license>CC0-1.0</metadata_license>
  <project_license>GPL-3.0+</project_license>
  <developer_name>System76</developer_name>
  <releases>
    <release urgency="high" version="${REVISION}" date="${DATE}" install_duration="15">
      <checksum filename="firmware.dfu" target="content"/>
      <url type="source">${SOURCE}</url>
      <description>
        <p>${DESCRIPTION}</p>
      </description>
    </release>
  </releases>
  <categories>
    <category>X-Device</category>
  </categories>
  <requires>
    <!-- TODO -->
    <id compare="ge" version="1.2.9">org.freedesktop.fwupd</id>
  </requires>
  <keywords>
    <keyword>dfu</keyword>
  </keywords>
  <custom>
    <value key="LVFS::UpdateProtocol">org.usb.dfu</value>
  </custom>
</component>
EOF

gcab \
    --verbose \
    --create \
    --nopath \
    "${BUILD}.cab" \
    "${BUILD}/"*

echo "created '${BUILD}.cab'"
