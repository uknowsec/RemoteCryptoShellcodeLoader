# RemoteCryptoShellcodeLoader

## 说明

Shellcode远程加载器
- 支持通过DomainFronting(aliyun)远程加载shellcode
- 远程获取shellcode使用aes动态加密传输数据

[ShellCode远程加载器改造计划
](https://uknowsec.cn/posts/notes/ShellCode%E8%BF%9C%E7%A8%8B%E5%8A%A0%E8%BD%BD%E5%99%A8%E6%94%B9%E9%80%A0%E8%AE%A1%E5%88%92.html)

## DomainFronting

阿里云申请的cdn地址不是w.cdngslb.com的话改一下加载器HttpConnect.cpp第63行的代码


## AES配置

### C++
main.cpp
```
	key = key + "123456";
	cryptopp::init(key, "0000000000000000");
```

- 修改拼接的6位字符内容
- 修改16位iv值

### Python

```
    key = key + "123456"
```
- 对应修改拼接的6位字符内容

```
   vi = '0000000000000000'
   text = ''

```
- 对应修改16位iv值
- 修改shellcode


## 编译依赖

### cryptopp

```
vcpkg install cryptopp
```
