/*
 * @file:    nginx_moufle_echo.c
 * @brief:   Nginx echo command output a string
 * @author:  Panda <vozlt@vozlt.com>
 * @version: 1.0.1
 * @date:    2017/6/12
 *
 * Compile:
 *           shell> ./configure --add-module=/path/to/nginx_moudle_echo.c
 *
 */

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

//定义模块配置结构   命名规则为ngx_http_[module-name]_[main|srv|loc]_conf_t。其中main、srv和loc分别用于表示同一模块在三层block中的配置信息。
typedef struct {
    ngx_str_t ed;  //该结构体定义在这里 https://github.com/nginx/nginx/blob/master/src/core/ngx_string.h
} ngx_http_echo_loc_conf_t;

/*//定义指令   ngx_command_s定义在core/ngx_config_file.h中
struct ngx_command_s {
    ngx_str_t      name;  //词条指令的名称
    ngx_uint_t     type;  //使用掩码标志位方式配置指令参数 具体参考https://github.com/nginx/nginx/blob/master/src/core/ngx_conf_file.h
    char           *(*set)(ngx_conf_t *cf, ngx_command_t *cmd, void *conf); //set是一个函数指针 用于指导一个参数化函数 具体参考https://github.com/nginx/nginx/blob/master/src/core/ngx_conf_file.h
    ngx_uint_t     conf; //指定Nginx相应配置文件内存其实地址，一般可以通过内置常量指定，如NGX_HTTP_LOC_CONF_OFFSET，offset指定此条指令的参数的偏移量。
    ngx_uint_t     offset;
    void           *post;
};*/

//定义echo模块的指令
static ngx_command_t ngx_http_echo_commands[] = {
        {ngx_string("echo"),
                NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
                ngx_http_echo,
                NGX_HTTP_LOC_CONF_OFFSET,
                offsetof(ngx_http_echo_oc_conf_t, ed),
                NULL,
        },
        ngx_null_command,
};

//参数转化函数
static char *
ngx_http_echo(ngx_conf_t *f,ngx_command_t *cmd , void *conf)
{
        ngx_http_core_loc_conf_t *clcf;
        clcf = ngx_http_conf_get_module_loc_conf(cf,ngx_http_core_module);
        clcf->handle = ngx_http_echo_handler;  //修改核心模块配置(也就是当前location),将其handler替换为我们自己定义的ngx_http_echo_handler
        ngx_conf_set_str_slot(cf,cmf,conf);
        return NGX_CONF_OK;
}