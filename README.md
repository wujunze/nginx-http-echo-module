# Practical development ginx Module
**[简体中文](http://git.oschina.net/wujunze/nginx_module_echo/blob/master/README_zh.md)**
## nginx_module_echo
echo string

## Nginx Version
Nginx1.0.10 https://github.com/nginx/nginx/releases/tag/release-1.0.10
![image](http://wx1.sinaimg.cn/large/005LOzcmly1fgimmvpk3sj30mi04p3z9.jpg)

## The development environment configuration
```shell
OS : CentOS Linux release 7.2.1511 (Core)
```
![image](http://wx4.sinaimg.cn/large/005LOzcmly1fgimnlvhh0j30s106imxw.jpg)
![image](https://wx4.sinaimg.cn/large/005LOzcmly1fgimnlwy1fj315u0dwdhn.jpg)

## Install a clean compile Nginx
1. Download a Nginx10.10 and unpack it
![image](http://wx2.sinaimg.cn/large/005LOzcmly1fgimq77ahwj30pw05et9n.jpg)

2. Install the GCC and the lib Nginx need
![image](https://wx4.sinaimg.cn/large/005LOzcmly1fgimv0hryoj30pd06djs8.jpg)
![image](https://wx4.sinaimg.cn/large/005LOzcmly1fgimva84bbj30pa07fgms.jpg)

3. ./configure --prefix=/usr/local/nginx && make && make install
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgimvz2rfkj30j10av75w.jpg)
![image](https://wx2.sinaimg.cn/large/005LOzcmly1fgimw6cmh2j30ur06n757.jpg)
![image](https://ws4.sinaimg.cn/large/005LOzcmly1fgimwezp9tj30qu0fdn0a.jpg)
4. Nginx run
![image](https://wx3.sinaimg.cn/large/005LOzcmly1fgimy3dkk5j30rr05ddh5.jpg)
![image](https://ws1.sinaimg.cn/large/005LOzcmly1fgimyc58d3j31vk0qsq9y.jpg)

## Definition module configuration structure
```C
typedef struct {
    ngx_str_t ed;  //该结构体定义在这里 https://github.com/nginx/nginx/blob/master/src/core/ngx_string.h
} ngx_http_echo_loc_conf_t;
```
![image](https://wx2.sinaimg.cn/large/005LOzcmly1fgin4at3rsj30rp04g74r.jpg)

#Define Nginx instruction and parameter conversion function
![image](https://wx1.sinaimg.cn/large/005LOzcmly1fgjdis37udj30xj0bktan.jpg)

## definition module Context
1. Define the type of ngx_http_module_t structure variables
![image](https://wx3.sinaimg.cn/large/005LOzcmly1fgjer4wtrxj313u09igo7.jpg)
2. Initialize a configuration structure
![image](https://wx1.sinaimg.cn/large/005LOzcmly1fgjerqnq71j30zd08fmyd.jpg)
3. Will the father block configuration information incorporated into this structure Implement the configuration of inheritance
![image](https://wx3.sinaimg.cn/large/005LOzcmly1fgjes12fy5j30ya08qgn7.jpg)

## Write the Handler really work part of the module
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgjfosnvf5j31hy0q6wlb.jpg)

## Combination Nginx module
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgjjo2l11jj31en0g4gq1.jpg)

## Finishing module code According to the Nginx official specification
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgjnxy9ikvj31yx12jwr3.jpg)

## Write the config file
```shell
ngx_addon_name=ngx_http_echo_module
HTTP_MODULES="$HTTP_MODULES ngx_http_echo_module"
NGX_ADDON_SRCS="$NGX_ADDON_SRCS $ngx_addon_dir/src/ngx_http_echo_module.c"
```
## make && make install
```shell
 ./configure --prefix=/usr/local/nginx/ --add-module=/root/ngx_dev && make && make install
```
## Successful installation
![image](https://ws3.sinaimg.cn/large/005LOzcmly1fgjnvxyqx4j30w40f0tbw.jpg)

## Modify the Nginx configuration file test Module
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgjnz17rh7j30jl07yaai.jpg)

## Nginx echo Module The successful running
![image](https://ws2.sinaimg.cn/large/005LOzcmly1fgjo0r1a5dj30yf06tmxv.jpg)

# If the repo help you welcome star fork    Thanks!

> ## reference
> 1. http://wiki.nginx.org/Configuration
> 2. http://tengine.taobao.org/book/
> 3. **http://blog.codinglabs.org/articles/intro-of-nginx-module-development.html**
> 4. https://www.nginx.com/resources/wiki/modules/
