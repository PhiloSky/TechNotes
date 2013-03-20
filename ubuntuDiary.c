/*******************************
	ubuntu使用笔记
*******************************/

/*-------------------------------------------------------
			全新安装ubuntu
-------------------------------------------------------*/
（一）分区方案
/分15G以上
/home分40G以上(越大越好，源码的git占8G，释放的源码4.7G，编译需要14G剩余空间，sdk有1.2G)
swap分内存大小即可
安装时如有更合适的软件源（比如国内的网易和各大高校的软件源）可不skip（跳过）下载文件，待安装完毕设置好软件源后执行更新即可
（二）安装完毕设置工作
安装显卡驱动
安装好语言支持之后再去升级安装其他软件包
更改一个较好的软件源，建议不要勾选proposed（提前释放的更新）这个源，因为容易引起版本太超前而其他依赖关系的软件跟不上
sudo apt-get update
sudo apt-get upgrade
强制安装i386版本的软件
sudo dpkg -i --force-all xxx.deb

新立得软件包管理器synaptic
chrome浏览器chromium-browser
beyondcompare


/*-------------------------------------------------------
			ubuntu本地化
-------------------------------------------------------*/
1.必备插件
# 以下所有软件都可以通过在UbuntuSoftware Center中进行搜索安装。
1）浏览器的 flash 插件：Adobe-flashplugin
2）播放器的MP3解码器：Fluendo codecs to decode mp3
3）播放器的多媒体解码包（四组）：
GStreamer extra plugins
GStreamer ffmpeg video plugin
GStreamer plugins for mms,wavpack,quicktime,mousepack
GStreamer plugins for aac,xvid,mpeg2,faad
以上插件的安装命令
sudo apt-get install flashplugin-installer gstreamer0.10-fluendo-mp3 gstreamer0.10-plugins-ugly gstreamer0.10-ffmpeg gstreamer0.10-plugins-bad gstreamer0.10-plugins-bad-multiverse

# 4）PDF 阅读器的文字编码包：poppler-data 
# 5）RAR 格式压缩解压：rar
# 6）7z 格式压缩解压：7zip
2.推荐的软件
# 1）CHM阅读器：chmsee
# 2）词典翻译工具：stardict 或者goldendict
# 3）FTP客户端：filezilla
# 4）PDF阅读器 Adobe reader
# 5）视频播放器 SMPlayer
# 6）Dock的安装  Cario-Dock 或者  Docky
# 7）跨平台工具 Adobe air  和 Wine  (关于wine的版本，我持保留意见，关于wine的使用我也持保留意见，很折腾就是了）
8）聊天工具: 
webqq桌面化
Beyond Compare 3.3.5 注册码 For Windows /Linux
注册码HmB5oANygQOhaStTHNa+zOKgOeWHOkeAp6d1+QwIebz6z9kwYCm9-O0jF9F79zvzed9v5UVC4VrDkDMmTM8nB+
#openfetion  终于见到能用的聊天工具了（保留意见，看该软件的评论）
#pidgin libqq—pidgin插件和飞信的插件也是不错的选择google上可以下到，也可以百度下添加源的方法
#9）下载工具： amule 类似电驴的东西

2.修改49-sansserif.conf解决pdf乱码问题（亲测）
sudo gedit /etc/fonts/conf.d/49-sansserif.conf
文件内容如下，“文泉驿微米黑”即是改好后的调用的字体名称
<?xml version="1.0"?>
<!DOCTYPE fontconfig SYSTEM "fonts.dtd">
<fontconfig>
<!--
If the font still has no generic name, add sans-serif
-->
    <match target="pattern">
     <test qual="all" name="family" compare="not_eq">
        <string>sans-serif</string>
        </test>
        <test qual="all" name="family" compare="not_eq">
            <string>serif</string>
        </test>
        <test qual="all" name="family" compare="not_eq">
            <string>monospace</string>
        </test>
        <edit name="family" mode="append_last">
  <string>文泉驿微米黑</string>
        </edit>
    </match>
</fontconfig>


/*-------------------------------------------------------
			问题处理
-------------------------------------------------------*/
（一）Ubuntu无法在模块路径中找到主题引擎：“pixmap”
这是gtk引擎出了问题，安装gtk引擎即可，命令：sudo apt-get install gtk2-engines-pixbuf
（二）gedit乱码处理
Windows下的txt用的是GBK编码，而getdit默认用的是UTF-8编码，所以会出现乱码。在11.10之前，可以通过gconf-editor来修改gedit的编码方式。在Ubuntu11.10上，改为dconf-editor。所以先安装gconf-editor。
打开终端，输入sudo apt-get install dconf-tools；
安装完成后，在终端输入dconf-editor并回车；
这时会打开一个界面，在界面的左边依次选择org——gnome——gedit——preferences——encodings；
选到encodings时，在右边双击auto-detected，添加'GB18030','GB2312','GBK'。输完后回车即可。这时候就能打开txt文档了。
也可以在终端通过命令行来解决。直接输入：
gsettings set org.gnome.gedit.preferences.encodings auto-detected "['UTF-8','GB18030','GB2312','GBK','BIG5','CURRENT','UTF-16']"
回车即可 
（三）去掉密钥环
打开应用程序－>附件－>密码和加密密钥（或在终端中输入 seahorse），切换到密码选项卡，会看到一个密码密钥环（我的密钥环是 login），右击－>更改密码，然后在“旧密码”中填入系统登录密码，其他不用填，直接确定，并选择“使用不安全的存储器”，这样就可以去掉默认密钥环的密码了。


/*-------------------------------------------------------
			Ubuntu常见命令
-------------------------------------------------------*/
1、在桌面添加‘’计算机‘’主文件夹‘’回收站‘’图标的操作：
按ALT＋F2，运行程序gconf-editor打开配置编辑器
选择apps→nautilus →desktop
勾选computer_icon_visible、home_icon_visible和trash_icon_visible边上的复选框。
马上就会在桌面上看到效果。
 
2、非常有用的清除系统垃圾文件命令：
终端里面输入：
sudo apt-get autoremove
sudo apt-get autoclean
sudo apt-get clean

3、清除已删除包的残余配置文件：
终端里面输入：dpkg-l |grep ^rc|awk '{print $2}' |sudo xargs dpkg-P
我从来都是直接将上面的命令复制到终端里面粘贴，省力省事省时。

4、播放RMVB文件，安装Mplayer播放器：sudoapt-get install mplayer
或者通过ubuntu软件中心安装gnomemplayer
 
5、双系统更改启动顺序：
# 亲测，注意是从0开始，如果是第6位，数字应该写5
我装的是XP和ubuntu10.10，默认启动顺序是ubuntu在第一位，XP在最后一位。经常用XP的话每次启动后都要手动选择比较麻烦。
只要打开终端输入：sudo gedit /boot/grub/grub.cfg
然后将set default="0"中的0改成4就OK。系统启动时XP排在第几位就改成相应的数字就行了。注意是从0开始，然后1.2.3.4
每次更新内核后需要重新设置
 
6、gnomemplayer 报错“无法打开VDPAUbackend libvdpau_nvidia.so: cannot open shared object file: No suchfile or directory”，但是可以正常打开视频。
原因：
gnomemplayer播放器默认vdpau为输出。而你没有安装vdpau，播放器自动转向x11了。
解决：
选择菜单“编辑”->“首选项”
“播放器”面板当中“视频输出:”设置为“xv”即可解决
 
7、快捷打开终端：Ctrl+Alt+T

8、安装五笔输入法：
系统装好后没有五笔，依次点击：系统－系统管理－语言支持，安装完整语言包，然后点击输入法处选择：首选项－输入法－选择输入法－汉语－五笔添加就OK了！ubuntu真的很方便。

9、花了3个小时，在线将10.10升级到11.04了，虽然有7、8个文件没有安装成功但是还是成功在使用，使用过程中问题比较多，一个一个来吧。用ubuntu软件中心安装compizconfig设置管理器时出现：

安装无法解决软件包依赖
这个错误可能是需要不存在或不可安装的软件包引起的。或者可能在软件包之间有冲突，它们不能同时安装。
详细信息 
下列软件包未满足的依赖关系：
simple-ccsm:
打开终端，输入sudoapt-get update之后，再输入sudoapt-get installcompizconfig-settings-manager，然后在“系统－首选项”找到“compizconfig设置管理器”设置即可。

10、系统更新命令：
update-manager-d
-c, --check-dist-upgrades 检查是否有新的Ubuntu发行版可用
-d,--devel-release 验证是否能够升级到最新版本
-p,--proposed 升级到最新版本的Ubuntu

11、在线升级到11.10了，出现很多错误提示，但是仍然能顺利进入系统，把compiz卸了。想用GNOME3，在网上找到以下方法：
（此PPA源仅适用于Ubuntu11.04/11.10版本）
sudoadd-apt-repository ppa:ricotz/testing
sudo apt-get update
sudoapt-get install gnome-shell
Gnome官方网站:http://live.gnome.org/GnomeShell
12、输入法图标不能正常显示
解决方法：点击键盘图标退出输入法，然后从系统-->首选项-->键盘输入法，重新启动输入法就OK了。我的11.04是这样解决的。

13、恢复gnome面板默认配置：
进入任一文件目录，选择编辑菜单－首选项－将显示隐藏和备份文件的勾选中，进入.gconf/apps/目录，删除目录下panel这个文件夹，注销后再进系统，面板将恢复默认设置。

14、sudoapt-get install gnome-sushi
安装后在Nautilus中选中某文件，按空格键后就可快速预览。

15、ubuntu11.10常用快捷键：
Super(windows图标键)打开托盘
Super+ A 打开应用程序托盘
Super+ F 打开文件及文件夹托盘
Super+ W 平铺模式列出所有窗口
Super+ S 浏览模式，缩小所有工作区，让你管理窗口
Super+ T 打开回收站
Ctrl+Alt+T打开终端
在终端中使用：
Ctrl+ a - 跳到行首
Ctrl+ b - 左移一个字符
Ctrl+ c - 终端进程
Ctrl+ d - 从光标处向右删除
Ctrl+ e - 跳到行尾
Ctrl+ f - 右移一个字符
Ctrl+ k - 删除从光标到行尾的部分
Ctrl+ u - 删除从光标到行首的部分
Ctrl+ l - 清屏，类似clear命令
Ctrl+ r - 查找历史命令

16、通过命令安装DEB软件：
要安装.deb套件包时
sudo dpkg -i package_file.deb
要反安装.deb套件包时
sudo dpkg -r package_name

17、安装软件时提示‘未安装软件包’等问题时试试sudoapt-get install-f

18、unity崩溃之后的解决方法
unity崩溃，进入unity后桌面上什么东西都没有，任务栏上什么都没有，解决方法：
Ctrl+Alt+T运行终端依次输入：
unity--reset，如果报错继续下面
cd
rm -rf .config/apps/compiz*
rm -rf .cache/compizconfig-1
rm-rf .config/compiz-1 
rm -rf .compiz

19、文件夹常用命令：
通常情况下，删除文件用：rm文件名
删除文件夹用：rmdir文件夹名
但是rmdir不能删除非空的文件夹，那如何删除非空文件夹呢：
命令：rm-rf 非空文件夹名
新建文件夹mkdir文件夹名
复制文件夹CP命令
格式:CP [选项]源文件或目录目的文件或目录
选项说明:
-b同名,备分原来的文件
-f强制覆盖同名文件
-r按递归方式保留原目录结构复制文件
cp-r /tmp/a /root/a
重命名文件夹
mvoldfilename newfilename

20、Ubuntu安装应用方法：
dpkg-i 软件名.deb
sudoapt-get install 软件名
sudoaptitute install 软件名
aptitue用法简介：
install- 安装/升级软件包。
remove- 卸载软件包。
purge- 卸载软件包并删除其配置文件。
hold- 将软件包置于保持状态。
unhold- 取消对一个软件包的保持命令。
markauto- 将软件包标记为已经自动安装。
unmarkauto- 将软件包标记为已经手动安装。
forbid-version- 禁止aptitude升级到某一特定版本的软件包。
update- 下载新/可升级软件包列表。
safe-upgrade- 执行一次安全的升级。
full-upgrade- 执行升级，可能会安装和卸载软件包。
build-dep- 安装软件包的编译依赖。
forget-new- 忘记哪些软件包是“新”的。
search- 按名称和/或表达式搜索软件包。
show- 显示一个软件包的详细信息。
clean- 删除已下载的软件包文件。
autoclean- 删除旧的已下载软件包文件。
changelog- 查看一个软件包的变更日志。
download- 下载软件包的.deb文件。
reinstall- 下载并(可能)重新安装一个现在已经安装了的软件包。
为什么-显示需要另一软件包的手动安装的软件包，或者
为什么一个或多个软件包需要给定的软件包
why-not- 显示导致与给定软件包包冲突的手动安装的包，或者为什么
如果安装一个或多个软件包会导致与给定软件包冲突。

选项：
-h此帮助文本。
--no-gui即使可用，也不使用GTK图形用户界面。
-s模拟动作，但是并不真正执行。
-d仅仅下载软件包，不安装或者卸载任何东西。
-P总是提示确认执行动作。
-y假设对简单的yes/no问题回答“yes”。
-F格式指定显示搜索结果的格式；参见手册。
-O次序指定如何排列显示搜索结果；参见手册。
-w宽度指定显示搜索结果的格式宽度。
-f积极地尝试修复损坏的软件包。
-V显示就要安装的软件包版本。
-D显示自动改变的软件包的依赖关系
-Z显示每个软件包的安装尺寸的变化。
-v显示附加信息。(可能会提供多次)。
-t[release] 设置将要从中安装软件包的发布版本。
-q在命令行状态下，不显示增量进度指示器。
-okey=val 直接设置名为“key”的配置选项。
--with(out)-recommends指定是否将推荐处理为强依赖关系。
-Sfname 从文件名中读取aptitude的扩展状态信息。
-u开始运行时下载新的软件包列表。
(只有终端界面)-i 开始运行时执行安装。
(只有终端界面)

22、ubuntu系统目录结构
/：根目录是所有目录的绝对路径的起始点，ubuntu中的所有文件和目录都在根目录下
/etc:此目录非常重要，绝大多数系统的相关服务的配置文件都保存在这里，这个目录的内容一般只能由管理员进行修改。（下面的源列表，网络设置文件……都在这个文件下）
/home：此目录是所有普通用户的宿主目录所在地，一般情况下，如果想要对用户进行磁盘限额功能，最好将此目录单独分区
/bin：放置有所有用户都能执行的命令
/sbin：一般放置系统管理员才能执行的命令
/dev：保存所有设备文件(/dev/hda1,/dev/cdrom……)
/mnt:作为挂载点用
/usr：包含了所有的命令、说明、程序库等（/usr/local包含管理员自己安装的程序，/usr/share包含文件的帮助文件，/usr/bin和/usr/sbin包含了所有命令）
/var：包含日志文件、计划性任务和邮件等
/lib：包含系统函数库文件
/lost+found：包含系统修复时的恢复文件
/tmp：包含了临时的文件，里面的文件可以随时删除
/boot：系统内核所在地，也是启动分区
/media：主要用于挂载多媒体设备
/root：系统管理员宿主目录

23、刚才打开ubuntu，我的版本是11.10，用的是gnome3.出现了如下错误提示：
E:Encountereda section with no Package: header, E:Problem with MergeList/var/lib/apt/lists/ubuntu.cn99.com_ubuntu_dists_oneiric_multiverse_i18n_Translation-en,E:The package lists or status file could not be parsed oropened.
在网上搜到了解决办法，现在记录下来，以便今后查阅：
终端中输入以下两条命令：
"$ sudorm /var/lib/apt/lists/* -vf 
"$ sudo apt-get update

24、升级软件命令：
sudoapt-get upgrade
清理无用的垃圾文件
自动卸载不用的包
sudoapt-get autoremove 
对已经删除的安装包留下的残余文件（配置文件）执行下面的命令进行清理：
dpkg-l |grep ^rc|awk '{print $2}' |tr ["\n"] [" "]|sudoxargs dpkg -P - 
或者dpkg-l |grep ^rc|awk '{print $2}' |sudo xargs dpkg -P
如果报错误，证明你的系统中没有残留配置文件了，无须担心。
清除缓存文件 
sudoapt-get clean
配置联通宽带，终端命令：
sudopppoeconf
一路回车
按照提示输入宽带用户名和密码
一路回车，大功告成。
--------------
fedora用户配置宽带的命令是
pppoe-setup
不过是用root权限。这个命令不能重复设置，容易出现ppp1,ppp2...就乱套了。

25、按内容查找文件：
进入该目录下
find |xargs grep "xxx"

26、生成软链接
ln -s 源文件路径 新文件
去掉-s就是硬链接
