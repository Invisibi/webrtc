# Develop with hooloop/webrtc docker image

## What's inside 

1. A Ubuntu 12.04 LTS with all dependencies needed for building WebRTC
2. Chromium source soft linked from our webrtc repo., under `/home/chromium-src`.

## Build with docker image

1. Install [Docker](https://www.docker.com/), [VirtualBox](https://www.virtualbox.org/) and [boot2docker](http://boot2docker.io/)
2. Get docker image by `docker pull hooloop/webrtc`
3. Clone our [fork of webrtc](https://github.com/Invisibi/webrtc)
4. Then you can start develop webrtc code in your host machine.
5. Once you want to build the webrtc libs, run the following command:

		docker run -v $YOUR_WEBRTC_CLONE_PATH:/home/Custom_WebRTC/webrtc/src $DESIRED_BUILD_OUTPUT_PATH:/home/Custom_WebRTC/libjingle_peerconnection_builds -t hooloop/webrtc /bin/bash --login -c "build_apprtc"

	Note: Remember to replace **$YOUR_WEBRTC_CLONE_PATH**, **$DESIRED_BUILD_OUTPUT_PATH**.


x86, x86_64 and armv7 libraries will be in $DESIRED_BUILD_OUTPUT_PATH after build process.

# Details for constructing hooloop/webrtc image

Below is the steps to recreate hooloop/webrtc docker image. If you have time to kill, you may try this.

## Prepare Environment

1. Install [Docker](https://www.docker.com/), [VIrtualBox](https://www.virtualbox.org/) and [boot2docker](http://boot2docker.io/)
2. Adjust boot2docker disk size as this [instruction](https://docs.docker.com/articles/b2d_volume_resize/)
3. Boot into an Ubuntu 12.04 LTS container 
4. Clone our fork of [webrtc-build-script](https://github.com/pristineio/webrtc-build-scripts) (which use git repo. instead of svn)

## Get/Update Code

1. Create directory for our custom webrtc project and set up environment var for it

	Here we assume the desired project location is **/home/Custom_WebRTC**.


		mkdir /home/Custom_WebRTC
		echo "export CUSTOM_WEBRTC_ROOT=/home/Custom_WebRTC" >> /.bashrc
		echo 'export PATH="$CUSTOM_WEBRTC_ROOT/depot_tools:$PATH"' >> /.bashrc
		echo "source /home/webrtc-build-scripts/android/build.sh" >> /.bashrc
		source /.bashrc

2. run `install_dependencies`
3. run `get_webrtc`

Note:

* If you encounter some packages (ex: msttcorefonts) not found issue, enable **multiverse** repo by editing */etc/apt/sources.lit*
* If some deps are missing, try running `$CUSTOM_WEBRTC_ROOT/webrtc/src/build/install-build-deps-android.sh`, `$CUSTOM_WEBRTC_ROOT/webrtc/src/build/install-build-deps.sh`

## Build


run `build_apprtc`, the built libs will appears in `$CUSTOM_WEBRTC_ROOT/libjingle_peerconnection_builds/`


## Reference

[Simple WebRTC standlone build with Git repo.](https://groups.google.com/forum/#!searchin/discuss-webrtc/Standalone%7Csort:date/discuss-webrtc/U01RHX9NIDA/sbnC2dA14XoJ)
