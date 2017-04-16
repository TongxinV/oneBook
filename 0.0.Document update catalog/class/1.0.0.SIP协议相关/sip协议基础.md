# SIP协议基础

[TOC]

### 1.SIP协议概念

1.1 SIP协议

> SIP 协议虽然属于应用层协议，然而 SIP 本身并不提供任何服务。但是 SIP 是通信的基础，在 SIP 这个通信的基础上可以用来构建不同的服务

SIP（会话发起协议）属于IP应用层协议，用于在IP网上为用户提供会话应用。会话（Session）指两方或多方用户之间的语音、视频、及其他媒体形式的通信，具体可能是IP电话、会议、即时消息等等

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-0001.gif" alt="p-sip-0001">
  
</p>



1.2 协议栈

SIP是一个信令协议，它对应于传统电话网络中的呼叫信令协议（比如SS7 ISUP）。构建一个完整多媒体通信架构还需要结合其他一些协议，必要的有：RTP，用于媒体传输；RSVP，用于QOS保证等等

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-0002.gif" alt="p-sip-0002">

</p>



1.3 基本功能

1.3.1会话的发起与管理

> SIP主要用于创建、修改和终止一个会话

一个**创建会话**的简单的例子如下图所示：

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-001.gif" alt="p-sip-001">
  
</p>


```
发起方向目的方发送一个SIP请求消息（INVITE），其中包含提议的会话参数的描述，请求在二者之间建立一个会话；
目的方返回一个SIP响应消息（200 OK），其中包含接受的会话参数的描述，接受会话建立请求
发起方发送一个SIP请求消息（ACK）确认会话的建立。
```

一个**修改会话**的简单例子如下图所示：

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-002.gif" alt="p-sip-002">
  
</p>

```
会话中的任意一方可以发送一个SIP请求消息（reINVITE），其中包含提议的新的会话参数，请求修改二者之间的会话；
另一方返回一个SIP响应消息（200 OK），其中包含接受的新的会话参数，接受会话修改请求
```

一个**结束会话**的简单例子如下图所示：

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-003.gif" alt="p-sip-003">
  
</p>

```
会话中的任意一方可以发送一个SIP请求消息（BYE），请求结束会话；
另一方返回一个SIP响应消息（200 OK），接受会话结束请求
```

1.3.2 用户位置管理

> 用于支持用户（终端）的移动性。猜测参与的服务器为注册服务器（Register Server）加位置服务器（Location Server）

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-004.gif" alt="p-sip-004">
  
</p>


### 2.SIP体系结构(基本网络模型)

> SIP协议组件：SIP 用户代理（User Agent，UA）和 SIP 用户服务器（User Server，US）

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-005.png" alt="p-sip-005">
  
</p>

**用户代理UA**本身又可分为：客户机端UAC（User Agent Client，用户代理客户机）和服务器端UAS（User Agent Server，用户代理服务器）。用户代理客户机是发起请求的主叫应用；客户代理服务器是通话的被呼叫端，主要负责接受、重定向或者拒绝请求，给到来的请求发送响应。用户代理在发起呼叫的时候它是用户代理客户端，而当被呼叫的时候它是用户代理服务器端

**用户服务器US**是 SIP 消息在到达其最终目的地前所经过的逻辑节点，这些服务器用于对请求进行路由和重定向，既进行名字解析和用户定位。主要包括以下几种服务器：

* 注册服务器(Registrar Server)：负责接收和处理 REGISTER 请求的服务器；
* 有状态代理服务器(Proxy Server)：负责接收和转发SIP请求。可解析并重构SIP消息的部分信息。但是这些重构不会影响请求或会话的状态
* 无状态代理服务器(Stateless Server)：其负责将上游的请求向下游转发和将下游的响应向上游转发，其不纪录请求或会话的状态
* 重定向服务器(Redirect Server)：负责将请求的地址映射为新地址；它对请求进行重定向但是不参与事务的处理
* 位置服务器(Location Server)：跟踪用户的位置；



### 3.SIP协议结构

> 事务用户层\事务层\传输层\语法和编码层

暂时没遇到要去分析这一层面的内容，有空再补充


### 4.SIP事务与SIP消息

> SIP每个操作体现为一个所谓的事务(由一个request、0到多个临时response以及一个最终response组成)

**SIP事务**：利用SIP实现的功能(比如语音业务、三方通话等)是通过SIP一些原子性的基本功能（比如注册（registration），发起会话（Initiation）、会话结束等）**组合**而成。每个原子性基本功能是通过一个SIP操作完成的。SIP操作基于类似HTTP的请求/响应事务模型，每个操作的调用过程体现为一个所谓**事务**。其中SIP请求消息中的方法（Method）指示出调用的操作

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-006.gif" alt="p-sip-006">
  
</p>

下表是在RFC 3261中定义的一些基本方法及其对应的SIP操作(不是全部):

| 方法Method    | SIP操作(事务)  | 
| :------------ |:---------------|
| INVITE        | 会话邀请(修改) |
| ACK           | 确认会话邀请   | 
| CANCEL        | 取消会话邀请   | 
| BYE           | 结束会话       |
| REGISTER      | 注册           | 
| OPTIONS       | 查询服务器能力 |

**SIP消息**：SIP 消息有两类：请求消息（request）和响应消息（response）。除了第一行分别是请求行（Request-Line）和状态行（Status-Line）以外(有统称为起始行start line)，SIP请求消息和SIP响应消息的剩下部分的组成基本类似，包括消息头域（message header）和消息体（message body）两部分

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-007.png" alt="p-sip-007">
  
</p>



#### SIP请求消息

根据请求行中的方法(method)的不同，SIP请求消息有很多种，分别完成各种操作的调用，不同操作可以自由组合以实现各种功能，下面进行简单的介绍：

* INVITE/**reINVITE**：INVITE 发起会话邀请。reINVITE（在已存在的对话中发送的INVITE称为reINVITE）修改已建立会话的参数
* ACK：完成会话建立的3次握手 [INVITE-200-ACK],仅仅用于INVITE
* BYE ：结束会话。
* CANCEL：取消正在建立中会话(INVITE已发送，但尚未收到最终响应（final response）)。
* **UPDATE**：更新会话参数。它被建议用于替代re-INVITE，与re-INVITE不同在于：它可以在初始INVITE未完成时发送，能用于在早对话(early dialog)中更新会话参数。

上面的5个请求可用于会话建立与管理

* REGISTER：登记UA当前的联系地址（contact）
* OPTIONS：查询服务器或对端UA的能力，具体包括支持的方法（method），扩展（extensions）、编解码（codecs）等。
 
* NOTIFY：事件通知，具体的事件包括、业务状态的改变（MWI，...），用户状态的改变等等。
* SUBSCRIBE：订阅/取消(Expires=0）事件通知。
* PUBLISH：发布事件状态。PUBLISH与REGISTER的相似之处在于：允许用户在另一个实体（状态管理实体/registrar）中创建、修改和移除自己的状态。对PUBLISH 请求的寻址与对于SUBSCRIBE 请求的寻址是一样的，PUBLISH 请求的Request-URI 中填入的是用户希望发布其事件状态的资源地址

上面的3个请求可构成SIP事件发布-订阅-通知机制

* INFO：发送会话中信息而不改变会话状态
* MESSAGE：通过在其请求体中承载即时消息内容实现即时通讯
* PRACK：用于回复一个临时性的请求
* **REFER**：使用这个REFER指向另一个电话，从而完成call transfer，联系第三方


#### SIP响应消息


|状态码|描述|例子|
|:---|:---|:---|
|1xx | Informational<br>请求收到，处理中             | 180 Ringing<br>181 Call is Being Forwarded |
|2xx | Success<br>操作已成功完成                     | 200 OK|
|3xx | Redirection<br>请求被重定向                   | 300 Multiple Choices<br>302 Moved Temporarily|
|4xx | Client Error<br>请求包含错误的文法，或者无法在本服务器上完成 | 401 Unauthorized<br>408 Request Timeout
|5xx | Server Error<br>请求有效，但服务器无法完成    | 503 Service Unavailable<br>505 Version Not Supported
|6xx | Global Failure<br>请求在任何服务器上都无法完成| 600 Busy Everywhere<br>603 Decline

关于每个错误码的具体含义见这里：[sip Response Codes(响应码)](https://github.com/TongxinV/xxxx001/blob/master/sip%20Response%20Codes(%E5%93%8D%E5%BA%94%E7%A0%81).md#sip-response-codes响应码)

关于错误的处理见这里：[...(略)文章根据工作遇到的再补充...]()


#### SIP消息头域

> 前6个头域是所有SIP消息中的必需的头域

| 消息头域 | 描述| 
|:---|:---|
| Via | 用于记录请求经由的路径<br>例：<br>Via: SIP/2.0/UDP 192.168.78.165:44794;branch=z9hG4bK-d87543-0625ef7c430eb355-1--d87543-;rport<br>Via:...<br>...<br>Via头域是被服务器插入request中，用来检查路由环的，并且可以使response根据via找到返回的路。**它不会对未来的request 或者是response造成影响** |
| Call-ID | 用于唯一标识一个特定的会话或注册消息<br>应具有随机性，保证全球唯一 | Call-ID: NGNlM...SDF...DIyYjQ |
| From | 源端SIP URL，标识请求发送方；UAC本地标签<br>例：<br>From: `"8888"<sip:8888@192.168.78.141>`;tag=b40d6a51<br>如果一个SIP消息中没有Contact或者Record-Route头域，那么callee就会根据From头域作为后续的Request消息头中的相关头域的内容，比如：如果Alice打一个电话给Bob，From头域的内容是 From:Alice<sip:alice@example.org>。那么Bob打给Alice时就会使用 sip:alice@example.org作为To头域和Request-URI头域的内容<br>**总的来说，如果有Route，request就应该根据Route发送，如果没有就根据Contact头域发送，如果连Contact都没有，就根据From头域发送** |
| To   | 目标SIP URL，标识请求接受方；UAS本地标签<br>例：<br>INVITE 中的To: `"1212"<sip:1212@192.168.78.141>`;<br>180响应中的To: `"1212"<sip:1212@192.168.78.141>`;tag=e9f70d91(由uas添加） |
| Max-Forwards | 消息最大转发次数。服务每次转发消息时将此域值减1，当变成0时，服务器发送 483响应（Too Many Hops response）|  |
| Cseq | 请求序列号，用于区分同一个会话中的不同请求 |
| | |
| Contact | 后续Request将根据Contact头域的内容决定目的地的地址，同时将Contact头域的内容放到Request-URI中 |
| Record-Route/Route |  Record-Route头域一般是被proxies插入到request中的，这样后续的Request如何有着和前面一样的call-id就会被路由到这些proxies，它也会被User Agent作为发送后续request的依据，Record-Route用于记录路由路径。将来用来构造request中的Route头域<br>详细细节可以参考http://blog.csdn.net/stefmoon/article/details/5532441 |
| | | 
| Supported | 列举出UAC或者UAS支持的扩展 | 
| Allow | 列举出UAC或者UAS支持的方法(method) |
| Accept | 接受的消息体(Body)协议，比如Http、SDP|
| Replace | Used to logically replace an existing SIP dialog with a new SIP dialog |

| |
|:---| 
| 其余省略 |



### 5.建立SIP会话流程实例(建立、修改和控制多媒体会话)

> 介绍SIP协议如何建立、修改和控制多媒体会话。这个事例介绍SIP的基本功能：用户定位、会话请求、通过协商会话参数建立会话和解除会话连接。 参考连接：https://www.ibm.com/developerworks/cn/opensource/os-cn-sip-intro/#major4

> 在学习SIP会自己搭建SIP服务器抓包学习，但是并不能真正贴近实际，下面例子虽然复杂了一点，但能理解更多东西。建议简单的会话先理解了之后，再过来看这部分内容


场景：Tom 在他的 PC 上使用一个 SIP 的应用程序呼叫 Internet 上另一个 SIP 电话用户 Jerry。

1. 注册过程

SIP 会话初始化协议的注册过程是建立用户当前 IP 地址与用户统一资源标识符之间的对应关系。


UA(用户)首先向服务器发送REGISTER请求。请求经过 P-CSCF（**代理**呼叫会话控制功能） 和 I-CSCF（**询问**呼叫会话控制功能）为 Tom 指定一个 S-CSCF（**服务**呼叫会话控制功能）。S-CSCF 负责根据请求信息建立用户标识与终端 IP 地址的对应绑定关系。<br>
（注：P-CSCF 是终端向网络中发送所有 SIP 消息的惟一入口。该实体在注册过程中用于 SIP 出站代理，注册完成后服务于所有其他 SIP 信令；注册完成后，后续请求或响应不再经过I-CSCF）

     REGISTER sip: telcomx.tel.com SIP2.0 
     From:<sip: tom@telcomx.tel.com>;tag=pohjaxx 
     To:<sip: tom@telcomx.com> 
     Via:SIP/2.0/UDP[4444::2:3:4:5];branch=xo93sle 
     Route: sip:[5555::a:f:f:e];lr 
     Contact:<sip:[4444::2:3:4:5]>;expires=600000 
     Call-ID: apb304a94sslfeiasle93aj11 
     Authorization:Digest username="tom@telcomx.tel.com", 
                  realm="telcomx.tel.com", 
                  nonce="", 
                  uri="sip:telcomx.tel.com", 
                  response=""
     CSeq: 25 REGISTER 
     Content-Length:0

* Route 标识请求路由的下一节点<br>
* Contact 中定义了 IP 地址与 SIP 统一资源标识符的绑定持续时间(expires)<br>
* Call-ID 和 CSeq 消息头惟一标识本次事务<br>

请求发送到该 S-CSCF 节点上， S-CSCF返回401（未授权）响应要求Tom进行认证，终端UA将发送第二个REGISTER请求，第二个请求包含相同的有关注册信息，但是第二个REGISTER产生一个新的Call-ID、Cseq号码、branch参数以及一个新的From标签，并且该REGISTER会带入新的安全认证标签信息

     REGISTER sip: telcomx.tel.com SIP2.0 
     From:<sip: tom@telcomx.com>;tag=6e87wa9 
     To:<sip: tom@telcomx.tel.com> 
     Via:SIP/2.0/UDP[4444::2:3:4:5];branch=u2x9s7 
     Route: sip:[5555::a:f:f:e];lr 
     Contact:<sip:[4444::2:3:4:5]>;expires=600000 
     Call-ID: apb304a94sslfaser2le93aj22 
     Authorization:Digest username="tom@telcomx.tel.com", 
                  realm="telcomx.tel.com", 
                  nonce="A34Cm+FVa73YTUGpGMBIs34P,algorithm=AKAv1-MD5", 
                  uri="sip:telcomx.tel.com", 
                  response="6629fac4969a87854152369874c43fd1"
     CSeq: 47 REGISTER 
     Content-Length:0

注:第二次注册请求会填写相应的认证密钥信息。认证过程成功，服务器US将对UA进行注册。即服务器创建一个绑定关系，绑定To消息头中公共用户标识和Contact中的IP访问地址。随后服务器向终端发送响应。

     SIP/2.0 200 OK 
     Via:SIP/2.0/UDP icscf1.tel.com;branch=21ksi9 
     Via:SIP/2.0/UDP pcscf1.tel.com;branch=2x7as2 
     Via:SIP/2.0/UDP[4444::2:3:4:5];branch=u2x9s7 
     From:<sip: tom@telcomx.tel.com>;tag=6e87wa9 
     To:<sip: tom@telcomx.tel.com>;tag=kotimaex 
     Contact:<sip:[4444::2:3:4:5]>;expires=600000 
     Service-Route:sip:telcomx@scscf1.tel.com;lr 
     Call-ID: apb304a94sslfaser2le93aj22 
     CSeq: 47 REGISTER 
     Content-Length:0

服务器将自己的访问地址通过Service-Route消息头返回给终端，该响应送回的路径是所有接收过REGISTER请求的网络单元，因为各个网络单元在接收 REGISTER 时都把自己的地址放在了Via消息头的顶端。这时终端注册已经成功。


<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-hhjl-001.jpg" alt="p-sip-hhjl-001">
  
</p>

2. 会话建立

Tom 通过 Jerry 的 SIP 标识呼叫 Jerry，这个统一资源标识符称作 SIP URI。SIP URI 很像一个 E-mail 地址，典型的统一资源标识符包括一个用户名和主机名。假设 Jerry 的统一资源标识符为 sip: jerry@california.tel.com。主机名 california.tel.com 是 Jerry 的本地 SIP 服务供应商即 Jerry 的归属域。Tom 使用自己的统一资源标识符发送请求。Tom 的统一资源标识符：sip: tom@telcomx.tel.com。其中 telcomx.tel.com 是 Tom 的 SIP 服务供应商

Tom 的软电话发送一个含有 Jerry 的统一资源标识符地址的 INVITE 请求。INVITE 是 SIP 的一个请求，其用于请求方发起请求希望服务方应答。建立会话的过程主要有以下几步：

* 使用 Jerry 的统一资源标识符创建 INVITE 请求
* 在 Contact 消息头中设置自己的访问 IP 地址与端口号，确保对端 Jerry 所有的响应都能直接包含以能发回到该终端
* 将注册过程中所存储的S-CSCF访问地址信息添加到消息的Route中，这样避免每次发送SIP请求需要通过I-CSCF查找S-CSCF的开销
* 将出站代理P-CSCF的访问地址也添加到Route消息头顶端生成消息路由
* 请求**去除Route中标识自己的访问条目**后，按照Route顶端地址发送到出站代理P-CSCF上，**在Record-Route和Via中添加P-CSCF访问条目**，确保请求的响应路由能够返回到自身节点。
* 转发INVITE请求到Route定义的下一个节点，请求发送到S-CSCF节点上，首先去除Route中标识自己的访问条目，将S-CSCF访问条目添加到Record-Route和Via中，查询DNS服务获得用户Jerry的SIP URI所归属的域，将请求转发到Jerry所归属域的I-CSCF节点上；
* 在Jerry归属域的I-CSCF节点上，首先**添加Jerry自己的访问条目(Route)**并将该访问条目添加到Via消息头中，查询SLF获取Jerry的HSS服务器地址，并查询HSS获取与用户Jerry相绑定的S-CSCF节点访问地址，将INVITE请求转发到该S-CSCF 节点上；
* 请求到达Jerry归属域的S-CSCF节点上，首先从路由Route消息头中删除标识自己的访问条目，在Record-Route中添加该访问条目，将用户Jerry的统一资源标识符替换为注册的联系地址，转发请求到下一个节点；
* 消息到达Jerry的P-CSCF代理节点上，其转发请到用户Jerry的 IP 地址上；

这时 INVITE 请求已经到达用户Jerry的终端上，该终端设备保存Tom的Contact消息头，生成相应响应信息，并设置响应Contact消息头为Jerry终端的IP地址/端口，将Record-Route和Via消息头复制到响应中，并基于Via消息头发送响应；<br>
当响应到达用于Tom终端时，Tom终端也会保存用户Jerry的Contact信息，这样双方都知道对方直接访问的IP地址和端口，之后可以直接发送请求到对方终端了(**没有Route要求的情况下**)

**INVITE 请求**

     INIVTE sip:jerry@california.tel.com 
     Via: SIP/2.0/UDP[4444::2:3:4:5];branch=8ulse1 
     Route:<sip:[5555::a:b:c:d];lr> 
     Route:<sip:telcomx@scscf1.tel.com;lr> 
     Contact:<sip:[4444::2:3:4:5]:1537> 
     From:<sip: tom@telcomx.tel.com>;tag=6e87wa9 
     To:<sip: jerry@california.tel.com> 
     Call-ID: apb03a0s09dkjdfoaidy49555 
     CSeq: 1 INVITE 
     Max-Forwards: 70 
     Content-Length:183 
    （必须的空行）
    （SDP 请求消息体）

**183“会话进行中”响应**

     SIP/2.0 183 Session in Progress 
     Via: SIP/2.0/UDP scscf2.california.tel.com;branch=12fd3 
     Via: SIP/2.0/UDP icscf2.california.tel.com;branch=24re3 
     Via: SIP/2.0/UDP scscf1.tel.com;branch=64w32 
     Via: SIP/2.0/UDP pcscf1.tel.com;branch=412d2 
     Via: SIP/2.0/UDP[4444::2:3:4:5];branch=8ulse1 
     Record-Route:<sip pcscf2.california.tel.com;lr> 
     Record-Route:<sip scscf2.california.tel.com;lr> 
     Record-Route:<sip scscf1.tel.com;lr> 
     Record-Route:<sip pcscf1.tel.com;lr> 
     Route:<sip:telcomx@scscf1.tel.com;lr> 
     Contact:<sip:[4444:5:6:7:8]:1078> 
     From:<sip: jerry@california.tel.com>;tag=e42q14d 
     To:<sip: tom@telcomx.tel.com>;tag=6e87wa9 
     Call-ID: apb03a0s09dkjdfoaidy49555 
     CSeq: 2 183 
     Max-Forwards: 70 
     Content-Length:165 
    （必须的空行）
    （SDP 请求消息体）

Tom发送INVITE请求后需要等待Jerry的响应，如果等待超时则需要重传一个INVITE请求，如果128秒后仍收不到响应，就宣告本次会话建立失败。例如本例中该呼叫漂洋过海，因此到达Jerry终端可能超过超时等待时间，为了避免Tom终端频繁地重发INVITE请求，Jerry的P-CSCF收到INVITE请求后，返回一个100Trying临时响应。这表明开始负责INVITE请求

SIP会话信号流程图：

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-hhjl-002.jpg" alt="p-sip-hhjl-002">
  
</p>


3. 会话建立时的会话媒体参数协商

> SIP Using SDP with Offer/answer Model。

呼叫建立时的媒体协商方式具体有六种可能的组合方式，主要了解了INVITE和200组合。**如何协商？answer包含与offer相同的媒体类型以及各类媒体支持的编码解码类型**

<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-hhjl-003.jpg" alt="p-sip-hhjl-003">
  
</p>

4. 会话建立后的会话媒体参数修改

会话中的任何时刻，任何参加者都可以发送新的offer修改会话特性，或者由于终端的媒体能力、地址等信息改变。可以增加新的媒体流，删除已经存在的媒体流，或者改变已经存在的媒体流的参数(比如修改媒体属性中的方向参数实现通话保持)等。相对与呼叫建立前的多种方案呼叫建立后的媒体参数修改要简单得多，使用的请求消息是INVITE，但由于是在呼叫过程中，我们通常称其为re-INVITE以示区别。于是呼叫建立后的媒体修改又分为两种：

(1)re-INVITE携带媒体能力，通过200OK携带协商结果<br>
(2)re-INVITE不携带媒体能力，200OK携带媒体能力，ACK携带协商结果


5. 会话的释放

Tom和Jerry通话完毕，Jerry按下终端设备的红色挂机按钮断掉呼叫。生成一个BYE请求，沿着与其他请求相同的路由发送给Tom终端，同时还会释放本次会话建立的媒体PDP(Packet Data Protocol分组数据协议)上下文。 Tom终端收到该请求后也会立刻释放它的PDP上下文，同时向Jerry终端返回一个200(OK)的响应来应答BYE请求。经过路径上的网络单元会清除与本次会话有关的所有会话状态和信息

     BYE sip:[4444::2:3:4:5] SIP/2.0 
     Route:<sip:pcscf2.california.com;lr> 
     Route:<sip:scscf2.california.com;lr> 
     Route:<sip:scscf1.tel.com;lr> 
     Route:<sip:pcscf1.tel.com;lr> 
     To:<sip: tom@telcomx.tel.com>;tag=6e87wa9 
     From:<sip: jerry@california.tel.com> 
     Call-ID: w273alskdjb732s07yad22 
     CSeq: 15 BYE 
     Max-Forwards: 70 
     Content-Length:0


<p align="center">
  <img src="https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-hhjl-004.jpg" alt="p-sip-hhjl-004">
  
</p>




[001]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-001.gif
[002]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-002.gif
[003]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-003.gif
[004]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-004.gif
[005]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-005.png
[006]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-006.png
[007]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/p-sip-007.png
