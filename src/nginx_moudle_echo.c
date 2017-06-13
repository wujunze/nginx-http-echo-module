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

/**
 * handler会接收一个ngx_http_request_t指针类型的参数，这个参数指向一个ngx_http_request_t结构体，此结构体存储了这次HTTP请求的一些信息，这个结构定义在https://github.com/nginx/nginx/blob/master/src/http/ngx_http_request.h中：
 *
 * 第一步是获取模块配置信息，这一块只要简单使用ngx_http_get_module_loc_conf就可以了。
 * 第二步是功能逻辑，因为echo模块非常简单，只是简单输出一个字符串，所以这里没有功能逻辑代码。
 * 第三步是设置response header。Header内容可以通过填充headers_out实现，我们这里只设置了Content-type和Content-length等基本内容，ngx_http_headers_out_t定义了所有可以设置的HTTP Response Header信息 这个结构体在https://github.com/nginx/nginx/blob/master/src/http/ngx_http_request.h 设置好头信息后使用ngx_http_send_header就可以将头信息输出，ngx_http_send_header接受一个ngx_http_request_t类型的参数。
 * 第四步也是最重要的一步是输出Response body。   Nginx的I/O机制  Nginx允许handler一次产生一组输出，可以产生多次，Nginx将输出组织成一个单链表结构，链表中的每个节点是一个chain_t，定义在https://github.com/nginx/nginx/blob/master/src/core/ngx_buf.h
 * @param r   ngx_http_request_t指针
 * @return
 */
static ngx_int_t
ngx_http_echo_handler(ngx_http_request_t *r)
{
    ngx_int_t rc;
    ngx_buf_t *b;
    ngx_chain_t out;
    ngx_http_echo_loc_conf_t *elcf;
    elcf = ngx_http_get_module_loc_conf(r,ngx_http_echo_module);
    if(!(r->method & (NGX_HTTP_HEAD|NGX_HTTP_GET|NGX_HTTP_POST)))
    {
        return NGX_HTTP_NOT_ALLOWED;
    }
    r->headers_out.content_type.len= sizeof("text/html") - 1;
    r->headers_out.content_type.data = (u_char *) "text/html";
    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = elcf->ed.len;
    if(r->method == NGX_HTTP_HEAD)
    {
        rc = ngx_http_send_header(r);
        if(rc != NGX_OK)
        {
            return rc;
        }
    }
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    if(b == NULL)
    {
        ngx_log_error(NGX_LOG_ERROR, r->connection->log, 0, "Failed to allocate response buffer.");
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }
    out.buf = b;
    put.next = NULL;
    b->pos = elcf->ed.data;
    b->last = elcf->ed.data + (elcf->ed.len);
    b->memory = 1;
    b->last_buf = 1;
    rc = ngx_http_send_header(r);
    if(rc != NGX_OK)
    {
        return rc;
    }
    return ngx_http_output_filter(r, &out);
}


























