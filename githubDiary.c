/*******************************
	github使用笔记
*******************************/

/*-------------------------------------------------------
			git下载命令
-------------------------------------------------------*/
将整个仓库下载下来，以后可以只下载最新的更新，注意后面的.git
以Android-Kitchen为例
首次下载：
git clone https://github.com/dsixda/Android-Kitchen.git
//github目录到名称是区分大小写的，如果提示远程链接不上，检查一下大小写

复制.git并改名为Android-Kitchen.git，放到想要存放仓库的上级目录，比如/~下
$ git clone Android-Kitchen.git
//即clone本地仓库Android-Kitchen.git
//不过这样origin就变成本地了，而不是远程的https://github.com/dsixda/Android-Kitchen.git了,到/.git/config文件中，将origin改回来

错误做法：
如果将.git放到~/Android-Kitchen下
1、在上级目录（/~）执行git clone https://github.com/dsixda/Android-Kitchen.git会提示/Android-Kitchen目录不为空
2、用git fetch origin（或者git pull origin，pull相当于fetch+merge）会抓取从你上次克隆以来别人上传到此远程仓库中的所有更新(或是上次 fetch 以来别人提交的更新)，所以结果是仅从.git中解压出最新的更新（改了哪些就解压哪些，而不是整体）


/*-------------------------------------------------------
		设定Github的SSH Key
-------------------------------------------------------*/
$ ssh-keygen -t rsa -C "committer_email@committermail.com"  
//创建个新的SSH key

设定存放目录和密码后把.ssh/id_rsa.pub的文件内容粘贴进github的帐号里
 
$ ssh -T git@github.com 
//测试是否成功  

如果出现"Agent admitted failure to sign using the key"
则解決方法是使用 ssh-add 指令将私钥 加进来（有多个密钥时，可根据实际情况改名xxx_rsa）
$ ssh-add   ~/.ssh/id_rsa

