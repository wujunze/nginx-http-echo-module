/*
 * @file:    nginx_moufle_echo.c
 * @brief:   Nginx echo command output a string
 * @author:  Panda <vozlt@vozlt.com>
 * @version: 1.0.1
 * @date:    2017/6/12
 *
 * Compile:
 *           shell> ./configure --add-module=/path/to/nginx_moudle_echo.c
 */

//定义模块配置结构
typedef struct {
    ngx_str_t ed;  //该结构体定义在这里 https://github.com/nginx/nginx/blob/master/src/core/ngx_string.h
} ngx_http_echo_loc_conf_t;