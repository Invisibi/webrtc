# Prepare the WebRTC Build Docker Image for Howler
 
You need to have ```docker``` (and ```boot2docker``` on OS X) already installed.
 
**1. Create persistent data volume (if not done already)**
```shell
docker run -v /webrtc --name hooloop-webrtc-data busybox true
docker run --rm -t --volumes-from hooloop-webrtc-data hooloop/webrtc:temp /bin/bash -lc "chown -R webrtc:webrtc /webrtc"
```
_Note: There is currently a bug in the image which you says that android/build.sh cannot be found. You can safely ignore this._

**2. Download sources**
```shell
docker run -w=/webrtc -u=webrtc --rm -t --volumes-from hooloop-webrtc-data hooloop/webrtc:temp /bin/bash -lc "git clone https://github.com/egistli/webrtc-build-scripts.git"
docker run -w=/webrtc -u=webrtc --rm -t --volumes-from hooloop-webrtc-data hooloop/webrtc:temp /bin/bash -lc "mkdir /webrtc/Custom_WebRTC"
docker run -w=/webrtc -u=webrtc --rm -t --volumes-from hooloop-webrtc-data hooloop/webrtc:temp /bin/bash -lc "get_webrtc"
```
_Note: This can take a long time depending on internet connection (20-100min)_

# Use the image to build WebRTC for Android
 
**1. Share data volume via OS X network share (only necessary once after booting up boot2docker)**
```shell
docker run --volumes-from hooloop-webrtc-data -p 548:548 --net=host -d hooloop/webrtc-share
```
_Note: To access the share, go to Finder. In sidebar "boot2docker" should appear or press ```CMD-K``` and enter ```afp://192.168.59.103``` (or whatever your docker ip is, enter ```boot2docker ip``` to find out). Connect as user: webrtc, password: webrtc_
 
**2. Trigger build**
```shell
docker run -w=/webrtc -u=webrtc --rm -t --volumes-from hooloop-webrtc-data hooloop/webrtc:temp /bin/bash -lc "build_apprtc"
```
 
_Notes_
- _Please note that there is currently a bug with Oh-My-Zsh shells that will sometimes **freeze** the command line when going to a git-directory on a network share. Just use ```/bin/bash``` instead if command line is required._
- _Please note that all builds etc needs to be triggered with user ```-u=webrtc```, otherwise you might lose write access to the network share for some files/directories. You can reown the whole ```/webrtc``` directory anytime by running_ ```chown -R webrtc:webrtc /webrtc``` as root.
- _If dependencies need to be updated/installed, this should of course be done as root. Make sure that /webrtc and all its content still belong to "webrtc" afterwards though (e.g. by running chown again._
 
# Building WebRTC Build Docker Image for Howler manually

The following steps are NOT necessary for building WebRTC. Go ahead if you want to build 
your own docker images, otherwise ignore anything below.
 
Create persistent docker volume 
```shell
docker run -v /webrtc --name hooloop-webrtc-data busybox true
```
 
Login to an Ubuntu container
```shell
docker run -it --volumes-from hooloop-webrtc-data ubuntu /bin/bash
```
 
Inside the docker container: 
```shell
apt-get update
apt-get -y install git vim software-properties-common
add-apt-repository multiverse
apt-get update
 
cd /webrtc
git clone https://github.com/egistli/webrtc-build-scripts.git
mkdir /webrtc/Custom_WebRTC
 
echo "export CUSTOM_WEBRTC_ROOT=/webrtc/Custom_WebRTC" >> ~/.bash_profile
echo 'export PATH="$CUSTOM_WEBRTC_ROOT/depot_tools:$PATH"' >> ~/.bash_profile
echo -e "source /webrtc/webrtc-build-scripts/android/build.sh\n" >> ~/.bash_profile
source ~/.bash_profile

# build once to make sure all dependencies are installed
install_dependencies
get_webrtc
cd $CUSTOM_WEBRTC_ROOT/webrtc/src/build
./install-build-deps-android.sh
./install-build-deps.sh
cd $CUSTOM_WEBRTC_ROOT
build_apprtc
 
# Update/Bugfix: use user "webrtc" for building in order to use OS X network share for better stability than samba
useradd --home /home/webrtc -m webrtc
echo webrtc:webrtc | chpasswd
cd /home/webrtc
mv /root/.bash_profile .
chown webrtc:webrtc .bash_profile
cd /root
ln -s /home/webrtc/.bash_profile .
cd /
chown -R webrtc:webrtc /webrtc
 
# Clean up to keep image small
apt-get clean autoclean autoremove
```

Get docker container id and commit changes
```shell
docker ps -a
docker commit -m "Setup build container for WebRTC" -a "Superman" <Container ID> hooloop/webrtc:temp
```
 
# Building WebRTC Network Share Docker Image manually
```shell
git clone https://github.com/mikumi/docker-timemachine.git
cd docker-timemachine
docker build -t=hooloop/webrtc-share .
```

## Reference

[Simple WebRTC standlone build with Git repo.](https://groups.google.com/forum/#!searchin/discuss-webrtc/Standalone%7Csort:date/discuss-webrtc/U01RHX9NIDA/sbnC2dA14XoJ)
