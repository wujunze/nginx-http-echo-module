# 实战开发一个Nginx拓展 (Nginx Module)
## nginx_module_echo
使用echo指令输出一个字符串

## Nginx 版本
Nginx1.0.10 https://github.com/nginx/nginx/releases/tag/release-1.0.10
![image](https://wx1.sinaimg.cn/large/005LOzcmly1fgimmvpk3sj30mi04p3z9.jpg)

## 开发环境
```shell
OS : CentOS Linux release 7.2.1511 (Core)
```
![image](https://wx4.sinaimg.cn/large/005LOzcmly1fgimnlvhh0j30s106imxw.jpg)
![image](https://wx4.sinaimg.cn/large/005LOzcmly1fgimnlwy1fj315u0dwdhn.jpg)

## 安装一个干净的 Nginx
1. 下载 Nginx10.10 并且解压它
![image](http://wx2.sinaimg.cn/large/005LOzcmly1fgimq77ahwj30pw05et9n.jpg)

2. 安装gcc和Nginx需要的lib
![image](https://wx4.sinaimg.cn/large/005LOzcmly1fgimv0hryoj30pd06djs8.jpg)
![image](https://wx4.sinaimg.cn/large/005LOzcmly1fgimva84bbj30pa07fgms.jpg)

3. ./configure --prefix=/usr/local/nginx && make && make install
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgimvz2rfkj30j10av75w.jpg)
![image](https://wx2.sinaimg.cn/large/005LOzcmly1fgimw6cmh2j30ur06n757.jpg)
![image](https://ws4.sinaimg.cn/large/005LOzcmly1fgimwezp9tj30qu0fdn0a.jpg)
4. 运行Nginx
![image](https://wx3.sinaimg.cn/large/005LOzcmly1fgimy3dkk5j30rr05ddh5.jpg)
![image](https://ws1.sinaimg.cn/large/005LOzcmly1fgimyc58d3j31vk0qsq9y.jpg)

## 定义模块配置结构
```C
typedef struct {
    ngx_str_t ed;  //该结构体定义在这里 https://github.com/nginx/nginx/blob/master/src/core/ngx_string.h
} ngx_http_echo_loc_conf_t;
```
![image](https://wx2.sinaimg.cn/large/005LOzcmly1fgin4at3rsj30rp04g74r.jpg)

#定义echo模块的指令和参数转化函数
![image](https://wx1.sinaimg.cn/large/005LOzcmly1fgjdis37udj30xj0bktan.jpg)

## 定义模块Context
1. 定义ngx_http_module_t类型的结构体变量
![image](https://wx3.sinaimg.cn/large/005LOzcmly1fgjer4wtrxj313u09igo7.jpg)
2. 初始化一个配置结构体
![image](https://wx1.sinaimg.cn/large/005LOzcmly1fgjerqnq71j30zd08fmyd.jpg)
3. 将其父block的配置信息合并到此结构体 实现了配置的继承
![image](https://wx3.sinaimg.cn/large/005LOzcmly1fgjes12fy5j30ya08qgn7.jpg)

## 编写Handler  模块真正干活儿的部分
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgjfosnvf5j31hy0q6wlb.jpg)

## 组合Nginx Module
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgjjo2l11jj31en0g4gq1.jpg)

## 整理模块代码 按照Nginx官方规范
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgjnxy9ikvj31yx12jwr3.jpg)

## 编写config文件
```shell
ngx_addon_name=ngx_http_echo_module
HTTP_MODULES="$HTTP_MODULES ngx_http_echo_module"
NGX_ADDON_SRCS="$NGX_ADDON_SRCS $ngx_addon_dir/src/ngx_http_echo_module.c"
```
## 编译安装echo模块
```shell
 ./configure --prefix=/usr/local/nginx/ --add-module=/root/ngx_dev && make && make install
```
## 安装成功
![image](https://ws3.sinaimg.cn/large/005LOzcmly1fgjnvxyqx4j30w40f0tbw.jpg)

## 修改Nginx配置文件测试Module
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgjnz17rh7j30jl07yaai.jpg)

## Nginx echo Module 运行成功
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgjo0r1a5dj30yf06tmxv.jpg)

>参考文献
 [1] Evan Miller, Emiller's Guide To Nginx Module Development. http://www.evanmiller.org/nginx-modules-guide.html, 2009
 [2] http://wiki.nginx.org/Configuration
 [3] Clément Nedelcu, Nginx Http Server. Packt Publishing, 2010
 [4] codinglabs http://blog.codinglabs.org/articles/intro-of-nginx-module-development.html