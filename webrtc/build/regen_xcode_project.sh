#!/bin/bash

# Export Environments

export GYP_CROSSCOMPILE=1
export GYP_DEFINES="OS=mac target_arch=x64"
export GYP_GENERATOR_FLAGS="xcode_project_version=3.2 xcode_ninja_target_pattern=All_iOS xcode_ninja_executable_target_pattern=AppRTCDemo|libjingle_peerconnection_unittest|libjingle_peerconnection_objc_test output_dir=out_ios"
export GYP_GENERATORS="ninja,xcode-ninja"

# Regenerate all.ninja.xcworkspace
BUILD_SCRIPT_DIR=$(dirname $0)
${BUILD_SCRIPT_DIR}/gyp_webrtc
