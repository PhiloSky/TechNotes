/*******************************
	Android源码编译笔记
*******************************/
//为了产生语法高亮效果方便阅读，本文档采用.c后缀名


/*-------------------------------------------------------
		编译前准备工作（64位ubuntu系统）
-------------------------------------------------------*/
//(摘抄自lewa Openbuild教程)

$ sudo apt-get install git gitk git-gui git-cola valgrind ssh git-core gnupg pngcrush flex bison gperf build-essential zip curl zlib1g-dev libc6-dev lib32ncurses5-dev ia32-libs x11proto-core-dev libx11-dev lib32z-dev libgl1-mesa-dev gcc gcc-multilib gcc-arm-linux-gnueabi gcc-arm-linux-gnueabihf g++ g++-multilib g++-arm-linux-gnueabi g++-arm-linux-gnueabihf mingw32 tofrodos python-markdown libxml2-utils lib32readline-gplv2-dev gcc-4.4 gcc-4.4-arm-linux-gnueabi gcc-4.4-arm-linux-gnueabihf gcc-4.4-multilib g++-4.4 g++-4.4-multilib g++-4.4-arm-linux-gnueabi g++-4.4-arm-linux-gnueabihf gcc-4.5 gcc-4.5-arm-linux-gnueabi gcc-4.5-arm-linux-gnueabihf gcc-4.5-multilib g++-4.5 g++-4.5-multilib g++-4.5-arm-linux-gnueabi g++-4.5-arm-linux-gnueabihf schedtool openjdk-*
//安装必要的软件包
//具体都有哪些软件包我也不清楚，但每次重装系统，这一条命令就可以搞定

$ mkdir ~/bin
//新建~/bin文件夹,~代表主文件夹

$ curl https://dl-ssl.google.com/dl/googlesource/git-repo/repo > ~/bin/repo
//从上述地址下载repo到bin文件夹

$ chmod a+x ~/bin/repo
//赋予repo可执行权限

$ gedit ~/.bashrc打开文件编辑器,在最后输入export PATH=$PATH:~/bin
//将bin文件夹添加到环境变量中
//如果要添加其他环境变量，继续在后面写“:路径”即可，如export PATH=$PATH:~/bin:~/apktool

$ source ~/.bashrc
//使环境变量生效（如果在~/目录下，直接写. .bashrc）


/*-------------------------------------------------------
			同步源码
-------------------------------------------------------*/
$ repo init -u git://github.com/CyanogenMod/android.git -b ics
//初始化CM源码仓库，2.3是gingerbread，4.1是jellybean

$ cd ~/cm9/.repo
$ ln -s ～/projects projects
//如果以前同步过CyanogenMod的任何源码，建议提取出projects文件夹单独存放，然后在要同步的目录下建立软链接

$ repo sync
//从CyanogenMod同步源码，默认是4线程，如果卡在某处很长时间，可尝试"repo sync -j2"强制使用2线程或更低线程

$ cp /home/hanife/xxxx/.repo/repo/repo /home/hanife/bin/repo
//如果提示repo不是最新，可以执行此命令来更新repo


/*-------------------------------------------------------
			source命令用法
-------------------------------------------------------*/
$ source FileName
//在当前bash环境下读取并执行FileName中的命令，该命令通常用"."来替代。
//如：source /etc/profile 与 . /etc/profile是等效的。


/*-------------------------------------------------------
			repo sync断点续传
-------------------------------------------------------*/
repo sync 下载代码的时候经常断。
断了之后，它又重新sync，浪费很多时间
可以直接到要下载的工程下面使用git fetch，可以断点续传
例如：
$ cd .repo/projects/prebuild
$ git fetch
前提是已经成功下载过一次，根目录下有该工程的WorkTree，比如prebuild.git对应prebuild目录


/*-------------------------------------------------------
			编译
-------------------------------------------------------*/
//摘自https://github.com/bluewater-cn/
//以编译espresso的CM9为例，确保/home分区至少有12G剩余空间

Setup vendor
  $ cd vendor/cm/
  $ ./get-prebuilts

Setup device
Connect phone to usb abd make sure debugging is avaliable for adb pulls
  $ cd ../../device/htc/espresso
  $ ./extract-files.sh
  //this pulls files from working espresso with most variants of shipped HTC ROM
  $ cd ../../..
//以上如果执行过一次，就不必再执行了

Setup environment
  $ source build/envsetup.sh
  $ lunch
  (select cm_espresso-userdebug)

Build CM9
  $ make otapackage -j2
//注意，必须用make otapackage，而不能只用make
//电脑配置较好可采用更高线程
//编译好的刷机包在out文件夹内

$ make distclean
//重新编译前清空out文件夹
