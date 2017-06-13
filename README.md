# Practical development ginx Module
**[简体中文](http://git.oschina.net/wujunze/nginx_module_echo/blob/master/README_zh.md)**
## nginx_module_echo
echo string

## Nginx Version
Nginx1.0.10 https://github.com/nginx/nginx/releases/tag/release-1.0.10
![nginx1.0.10.png](https://ooo.0o0.ooo/2017/06/13/593fc07b90e28.png)

## The development environment configuration
```shell
OS : CentOS Linux release 7.2.1511 (Core)
```
![Server_info.png](https://ooo.0o0.ooo/2017/06/13/593fc07b5dff4.png) 
![Server_CPU_info.png](https://ooo.0o0.ooo/2017/06/13/593fc0825053e.png)

## Install a clean compile Nginx
1. Download a Nginx10.10 and unpack it
![nginx1.0.10.png](https://ooo.0o0.ooo/2017/06/13/593fc07cd07e2.png)

2. Install the GCC and the lib Nginx need
![install_GCC.png](https://ooo.0o0.ooo/2017/06/13/593fc06152dd0.png)
![Nginx_lib.png](https://ooo.0o0.ooo/2017/06/13/593fc078c3c2b.png)

3. ./configure --prefix=/usr/local/nginx && make && make install
![configure_ok.png](https://ooo.0o0.ooo/2017/06/13/593fc061b5a9f.png)
![make && make install.png](https://ooo.0o0.ooo/2017/06/13/593fc074c9b29.png)
![nginx_install_ok.png](https://ooo.0o0.ooo/2017/06/13/593fc080db608.png)

4. Nginx run
![start_nginx.png](https://ooo.0o0.ooo/2017/06/13/593fc08044567.png)
![nginx_install_ok.png](https://ooo.0o0.ooo/2017/06/13/593fc080db608.png)

## Definition module configuration structure
```C
typedef struct {
    ngx_str_t ed;  //该结构体定义在这里 https://github.com/nginx/nginx/blob/master/src/core/ngx_string.h
} ngx_http_echo_loc_conf_t;
```
![define_moudle_conf.png](https://ooo.0o0.ooo/2017/06/13/593fc0615456f.png)

## Define Nginx instruction and parameter conversion function
![定义指令和参数转化函数.png](https://ooo.0o0.ooo/2017/06/13/593fc0529132f.png)

## definition module Context
1. Define the type of ngx_http_module_t structure variables
![定义注入点结构体.png](https://ooo.0o0.ooo/2017/06/13/593fc052953a4.png)
2. Initialize a configuration structure
![初始化一个配置结构体.png](https://ooo.0o0.ooo/2017/06/13/593fc05277601.png)
3. Will the father block configuration information incorporated into this structure Implement the configuration of inheritance
![合并父block的配置信息.png](https://ooo.0o0.ooo/2017/06/13/593fc0528ec4a.png)

## Write the Handler really work part of the module
![Nginx模块handler.png](https://ooo.0o0.ooo/2017/06/13/593fc0616a385.png)

## Combination Nginx module
![组合Nginx Module.png](https://ooo.0o0.ooo/2017/06/13/593fc052aa29a.png)

## Finishing module code According to the Nginx official specification
![ok_file.png](https://ooo.0o0.ooo/2017/06/13/593fc061b7d7a.png)

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
![make install.png](https://ooo.0o0.ooo/2017/06/13/593fc052be07d.png)

## Modify the Nginx configuration file test Module
![test module.png](https://ooo.0o0.ooo/2017/06/13/593fc0614f91a.png)

## Nginx echo Module The successful running
![module ok.png](https://ooo.0o0.ooo/2017/06/13/593fc05292b08.png)

# If the repo help you welcome star fork    Thanks!

> ## reference
> 1. http://wiki.nginx.org/Configuration
> 2. http://tengine.taobao.org/book/
> 3. **http://blog.codinglabs.org/articles/intro-of-nginx-module-development.html**
> 4. https://www.nginx.com/resources/wiki/modules/

