# RemoteCryptoShellcodeLoader

## 说明
Shellcode远程加载器
- 支持通过DomainFronting(aliyun)远程加载shellcode
- 远程获取shellcode使用aes动态加密传输数据

注：cdn地址不是w.cdngslb.com的话改一下加载器HttpConnect.cpp第63行的代码

## 依赖安装

### cryptopp

```
vcpkg install cryptopp
```
