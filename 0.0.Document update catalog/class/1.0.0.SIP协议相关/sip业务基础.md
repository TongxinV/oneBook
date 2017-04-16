# SIP业务基础

[TOC]


* 呼叫等待
* 呼叫保持
* 呼叫转移
* 呼叫前转
* 三方通话


### 呼叫等待

> 通话期间，有新用户打进来，新进来的用户被置于等待；案例还包括了呼叫保持过程

![wh-hjdd][101]

(1)新进用户C发起INVITE请求，A先向B发送**182 Queues**响应，然后A发起与B呼叫保持请求，请求成功后(与B呼叫保持)，响应200OK给C，C回应ACK，A与C通话<br>
(2)A要恢复与B的通话需要重新发起请求消息

---

### 呼叫保持

> 暂停与原来的电话(呼叫保持)， 打出新的电话

![wh-hjbc][201]

...
用户A按下呼叫保持键，代理终端A向代理服务器发送Invite消息，请求与代理终端B呼叫保持，然后呼出新的电话(C)

**问**：**呼叫保持怎么实现**？**同样是INVITE请求，如何判断这个INVITE是用来实现呼叫保持的**?

> 参考文章：[《SIP通话中Hold功能的实现 》](http://blog.sina.com.cn/s/blog_414e587f010008oh.html)

通过INVITE携带的SDP内容不同来实现，用于呼叫保持的`INVITE中的SDP`/`对方回复200 OK中的SDP`主要特殊地方：

![hold][204]


而正常的INVITE和200 OK中SDP的媒体属性(a)都为**sendrecv**

---

### 呼叫转移

> 接受REFFER请求并主动向第三方呼叫

#### 呼叫转移（盲转）

> 座席电话拍叉后拨打相应电话，然后直接挂机



![wh-hjzy-m][301]

...<br>
(1)用户A按下呼叫保持键，代理终端A向代理服务器发送Invite消息，请求与代理终端B呼叫保持(in-dialog)，然后呼出新的电话(C)并挂机。用户A对B发送REFER请求，B接受REFER请求并主动向C呼叫(B呼叫C之前会向A发送呼叫保持请求)<br>
(2)结束A、B之间对话：A发起BYE请求（注：也可以由B来发起）


#### 呼叫转移（询问）

> 座席电话拨打相应电话后，等待 `响铃或通话成功后讯问` 后再进行下一步处理

![wh-hjzy-xun][303]

...<br>
(1)用户A按下呼叫保持键，代理终端A向代理服务器发送Invite消息，请求与代理终端B呼叫保持(in-dialog)，然后呼出新的电话(C)并与C建立对话<br>
(2)A挂掉电话，用户A对B发送REFER请求，B接受REFER请求并主动向C呼叫(B呼叫C之前会向A发送呼叫保持请求)<br>
(3)结束`A、B之间` `A、C`对话：B通过replace扩展，替代原来与A的对话；C发起BYE请求结束

---

### 呼叫前转（无应答、遇忙和无条件）

> 略


---

### 三方通话

> 前提条件：B开通三方通话；操作流程：1、B呼A，A接听；2、B拍叉呼C；3、C接听；4、B拍叉按3；

![wh-sfth-01][401]

(1)AB通话<br>
(2)A按下拍叉键，与B呼叫保持(re-INVITE)<br>
(3)A呼叫C(INVITE)，AC通话<br>
(4)A按下拍叉键，与C呼叫保持(re-INVITE)<br>
(5)A按下3键向B、C发送INVITE解保持，三方通话（注：此时B、C是没有建立通话的，而是经过A这里的语音混合之后再发给B、C）<br >

















[101]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/01%E5%91%BC%E5%8F%AB%E7%AD%89%E5%BE%85%E6%8A%A5%E6%96%87%26%E5%9B%BE%E7%89%87/ws-hjdd-001.png
[201]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/02%E5%91%BC%E5%8F%AB%E4%BF%9D%E6%8C%81%E6%8A%A5%E6%96%87%26%E5%9B%BE%E7%89%87/wh-hjbc-001.png
[202]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/02%E5%91%BC%E5%8F%AB%E4%BF%9D%E6%8C%81%E6%8A%A5%E6%96%87%26%E5%9B%BE%E7%89%87/hold-001.png
[203]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/02%E5%91%BC%E5%8F%AB%E4%BF%9D%E6%8C%81%E6%8A%A5%E6%96%87%26%E5%9B%BE%E7%89%87/hold-002.png
[204]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/02%E5%91%BC%E5%8F%AB%E4%BF%9D%E6%8C%81%E6%8A%A5%E6%96%87%26%E5%9B%BE%E7%89%87/hold.png
[301]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/03%E5%91%BC%E5%8F%AB%E8%BD%AC%E7%A7%BB%E6%8A%A5%E6%96%87%26%E5%9B%BE%E7%89%87/wh-hjzy-m-01.png
[302]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/03%E5%91%BC%E5%8F%AB%E8%BD%AC%E7%A7%BB%E6%8A%A5%E6%96%87%26%E5%9B%BE%E7%89%87/wh-hjzy-m-02.png
[303]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/03%E5%91%BC%E5%8F%AB%E8%BD%AC%E7%A7%BB%E6%8A%A5%E6%96%87%26%E5%9B%BE%E7%89%87/wh-hjzy-xun-01.png
[401]:https://raw.githubusercontent.com/TongxinV/xxxx001/master/assets/04%E5%91%BC%E5%8F%AB%E8%BD%AC%E7%A7%BB%E6%8A%A5%E6%96%87%26%E5%9B%BE%E7%89%87/wh-sfth-01.png