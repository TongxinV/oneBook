##题目待定
###uboot源码分析
结构：

    project
        ├── start.S
        │   ├── 1.包含头文件
        │   ├── 2.定义4个4字节变量填充占位
        │   ├── 3.构建异常向量表，程序跳转到reset符号处
        │   └── 4.reset
        │       ├── msr cpsr_c, #0xd3           将CPU设置为禁止 FIQ\IRQ.ARM状态.SVC模式
        │       ├── cpu_init_crit               CPU初始化，完成L2Cache.L1Cache.MMU设置
        │       ├── Read booting information    加载启动信息，主要完成了识别并暂存启动介质类型
        │       ├── 设置栈.为了在内部96KB的iRAM中使用栈；并调用lowlevel_init
        │       |   lowlevel_init
        |       |       push {lr}
        |       |       check reset statue
        |       |       IO Retension release
        |       |       Disable Watchdog
        |       |       供电锁存
        |       |       判断当前代码是在SRAM中还是DDR中执行 以决定是否跳过下面的时钟和DDR初始化
        |       |           system_clock_init
        |       |           mem_ctrl_asm_init
        |       |       初始化串口，并打印‘OK’
        |       |       pop {pc}
        │       ├── 设置栈. 为了将来重定位之后能在内存中使用栈；判断当前代码是在SRAM中还是DDR中执行 以决	定是否进行重定位movi_bl2_copy
        |       └── pop {pc}
        |    
        |       └── c.php
        │           │   ├── IO Retension release
        │   │   │   │   ├── Disable Watchdog
        │   │   │   │   ├── 供电锁存
        │   │   │   │   ├── 判断当前代码是在SRAM中还是DDR中执行 以决定是否跳过下面的时钟和DDR初始化
                                fff
        │   │   │   │   ├── lowlevel_init
        │   │   ├── b.css
        │   │   ├── b.css
        │   │   ├── b.css
        │   │   ├── b.css
        │   │   └── a.php
        │   │   └── a.php
        │   │   └── a.php
        │   ├── b
        │   │   ├── b.css
        │   │   ├── b.js
        │   │   └── b.php
        │   └── c
        │       ├── c.css
        │       ├── c.js
        │       └── c.php
        ├── bootstrap.css
        ├── bootstrap.js
        ├── index.php
        └── jquery.js

如果我们可以使用工具扫描整个project目

考虑这样的目录结构：

    project
        ├── widget
        │   ├── a
        │   │   ├── a.css
        │   │   ├── a.js
        │   │   └── a.php
        │   ├── b
        │   │   ├── b.css
        │   │   ├── b.js
        │   │   └── b.php
        │   └── c
        │       ├── c.css
        │       ├── c.js
        │       └── c.php
        ├── bootstrap.css
        ├── bootstrap.js
        ├── index.php
        └── jquery.js

如果我们可以使用工具扫描整个project目
