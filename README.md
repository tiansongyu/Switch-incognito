![CI](https://github.com/tiansongyu/Switch-incognito/workflows/CI/badge.svg)
<div>
  <span>简体中文</span> /<a href=".github/README-English.md">English</a>
</div>

# incognito
![image](https://github.com/tiansongyu/Switch-incognito/blob/master/res/display.jpg)
删除任天堂swtich的联网序列号
注意:Atmosphere系统需要写入PRODINFO，所以您必须使用ReiNX、SX OS或自定义的KIP来安装它，安装后，需要切换回大气层系统。

# Compiling
Building needs a working devkitA64 environment, with packages `libnx`,`deko3d` and `switch-glm` installed (`sudo (dkp-)pacman -S switch-dev`).
```
$ git clone --recursive https://github.com/tiansongyu/Switch-incognito.git
$ cd Switch-incognito
$ make -j$(nproc)
```
Output will be located in /.



## 功能
- a)删除机器联机序列号，而不用担心被Ban。
- b)防止恶意的自制程序窃取你的个人证书。
- c)删除序列号后，除任天堂服务器外，其他服务器都可正常连接
- d)支持多国语言(目前支持中文和英文)
## 免责声明
* 此应用程序不会删除您的Switch上的所有个人信息，也不应该被视为防止被禁止的真正预防措施。
始终要有一个NAND备份。我不负责任何被Ban的后果。使用风险自负，因为这是一个实验项目。

* 这个应用程序将你的PRODINFO备份到SD卡上，作为backup/PRODINFO。你应该把这个备份放在一个更安全的位置，不要把它留在SD卡上，不然可能会被损坏或被恶意应用程序读取。
