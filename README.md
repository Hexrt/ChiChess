### 中国象棋-广域网联机版

- 大一上C语言课设

#### 概况

- 此项目为大一上学期的课程设计

  编译器使用的是VS2019

  依赖的图形库为 EasyX2018春分版

- 客户端

  - Win10(64位)
  - VisualStudio2019默认编译

- 服务端

  - 环境是CentOS Linux release 8.0.1905
  - g++编译

- 主要功能

  - 在线联机模式
  - 本地离线模式
  - 棋局回看模式

- 开发周期 10天左右

- 开源地址 https://github.com/Hexrt/ChiChess

#### 快速起步

**三步**

- 拉取源码，修改

  在Server目录下修改`Server.cpp`

  ```cpp
  #define PORT 6666//监听端口
  ```

- 在客户端源码目录下的`my_define.h`中找到服务器配置行

  修改为部署好的服务器信息(与上面一致)

  ```cpp
  #define SERVER_IP "127.0.0.1"//服务器广域网ipv4地址
  #define SERVER_PORT 6666//监听端口
  ```

- 编译运行Server



2020年6月5日10点41分

By **Hexrt**