# nginx_module_echo
使用echo指令输出一个字符串

# Nginx 版本
Nginx1.0.10 https://github.com/nginx/nginx/releases/tag/release-1.0.10
![image](https://wx1.sinaimg.cn/large/005LOzcmly1fgimmvpk3sj30mi04p3z9.jpg)

# 开发环境
```shell
OS : CentOS Linux release 7.2.1511 (Core)
```
![image](https://wx4.sinaimg.cn/large/005LOzcmly1fgimnlvhh0j30s106imxw.jpg)
![image](https://wx4.sinaimg.cn/large/005LOzcmly1fgimnlwy1fj315u0dwdhn.jpg)

# 安装一个干净的 Nginx
1. Download a Nginx10.10 and unpack it
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

# 定义模块配置结构
```C
typedef struct {
    ngx_str_t ed;  //该结构体定义在这里 https://github.com/nginx/nginx/blob/master/src/core/ngx_string.h
} ngx_http_echo_loc_conf_t;
```
![image](https://wx2.sinaimg.cn/large/005LOzcmly1fgin4at3rsj30rp04g74r.jpg)

#定义echo模块的指令和参数转化函数
![image](https://wx1.sinaimg.cn/large/005LOzcmly1fgjdis37udj30xj0bktan.jpg)

