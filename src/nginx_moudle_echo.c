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

//创建合并配置信息 定义模块Context
/**
 * 定义ngx_http_module_t类型的结构体变量   命名规则为ngx_http_[module-name]_module_ctx，这个结构主要用于定义各个Hook函数
 *
 * 可以看到一共有8个Hook注入点，分别会在不同时刻被Nginx调用，由于我们的模块仅仅用于location域，这里将不需要的注入点设为NULL即可。
 *
 * ngx_http_echo_create_loc_conf  ngx_http_echo_merge_loc_conf 这两个函数会被Nginx自动调用。注意这里的命名规则：ngx_http_[module-name]_[create|merge]_[main|srv|loc]_conf。
 */
static ngx_http_module_t ngx_http_echo_module_ctx = {
        NULL,                                  /* preconfiguration */
        NULL,                                  /* postconfiguration */
        NULL,                                  /* create main configuration */
        NULL,                                  /* init main configuration */
        NULL,                                  /* create server configuration */
        NULL,                                  /* merge server configuration */
        ngx_http_echo_create_loc_conf,         /* create location configration */
        ngx_http_echo_merge_loc_conf           /* merge location configration */
};

/**
 * 初始化一个配置结构体
 * @param cf
 * @return
 */
static char *
ngx_http_echo_create_loc_conf(ngx_conf_t *cf)
{
        ngx_http_echo_loc_conf_t *conf;
        conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_echo_loc_conf_t)); //gx_pcalloc用于在Nginx内存池中分配一块空间，是pcalloc的一个包装
        if(conf == NULL) {
                return NGX_CONF_ERROR;
        }
        conf->ed.len = 0;
        conf->ed.data = NULL;
        return conf;
}
/**
 * 将其父block的配置信息合并到此结构体 实现了配置的继承
 * @param cf
 * @param parent
 * @param child
 * @return ngx status code
 *
 * ngx_conf_merge_str_value不是一个函数，而是一个宏，其定义在https://github.com/nginx/nginx/blob/master/src/core/ngx_conf_file.h#L205中
 */
static char *
ngx_http_echo_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child)
{
    ngx_http_echo_loc_conf_t *prev = parent;
    ngx_http_echo_loc_conf_t *conf = child;
    ngx_conf_merge_str_value(conf->ed, prev->ed, '"');
    return NGX_CONF_OK;
}