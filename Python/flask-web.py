# coding=utf-8
from flask import Flask, jsonify
from flask import request
from Crypto.Cipher import AES
from flask import make_response
import os
from flask import Flask, render_template, request, redirect
import base64
app = Flask(__name__)

def AES_Encrypt(key):
    BS = AES.block_size
    pad = lambda s: s + (BS - len(s) % BS) * chr(BS - len(s) % BS)
    unpad = lambda s : s[0:-ord(s[-1])]

    key = key # the length can be (16, 24, 32)
    vi = '0000000000000000'
    text = 'fce8890000006089e531d2648b52308b520c8b52148b72280fb74a2631ff31c0ac3c617c022c20c1cf0d01c7e2f052578b52108b423c01d08b407885c0744a01d0508b48188b582001d3e33c498b348b01d631ff31c0acc1cf0d01c738e075f4037df83b7d2475e2588b582401d3668b0c4b8b581c01d38b048b01d0894424245b5b61595a51ffe0585f5a8b12eb865d686e6574006877696e6954684c772607ffd5e80000000031ff5757575757683a5679a7ffd5e9a40000005b31c951516a03515168bb01000053506857899fc6ffd550e98c0000005b31d252680032c08452525253525068eb552e3bffd589c683c350688033000089e06a04506a1f566875469e86ffd55f31ff57576aff5356682d06187bffd585c00f84ca01000031ff85f6740489f9eb0968aac5e25dffd589c16845215e31ffd531ff576a0751565068b757e00bffd5bf002f000039c775075850e97bffffff31ffe991010000e9c9010000e86fffffff2f6c6f676f33327833322e676966005cfc3c0e95c33e5b83b66b64995a2658719abdb0e9a273af0e87851b95c5acc982feee94857ab5093d530812d0074c3a0bd4c2bb342eead36ab5ef16a68f5d32004163636570743a20746578742f68746d6c2c6170706c69636174696f6e2f786d6c3b2a2f2a3b0d0a4163636570742d456e636f64696e673a20677a69702c206465666c6174650d0a557365722d4167656e743a204d6f7a696c6c612f352e3020286950686f6e653b20435055206950686f6e65204f532031315f30206c696b65204d6163204f53205829204170706c655765624b69742f3630342e312e33380d0a486f73743a2077782e71712e636f6d0d0a007c2d35c5a8a3231b119f028136c2db9b573db2293328652006043153d3e7905bfbcd29d9895f58eec41c7c1b187d73f3f1cd3a83a082e3ad29efc4a2d6532d4c2ca6335de5e4d2c94890b445843105cac7f6e6de09fdd35419e406b17ebbe3defaf587bf9c1a2dc37f24ea0a1e1ef5dcb009ce338c0790158f1443d10068f0b5a256ffd56a4068001000006800004000576858a453e5ffd593b90600000001d9515389e7576800200000535668129689e2ffd585c074c68b0701c385c075e558c3e889fdffff33362e3130322e3231322e37310012345678'

    cipher = AES.new(key.encode('utf8'), AES.MODE_CBC, vi.encode('utf8'))

    encrypted = cipher.encrypt(pad(text)).encode('hex')
    return str(encrypted)


@app.errorhandler(404)
def miss(e):
    return redirect("http://wx.qq.com")
 
@app.errorhandler(500)
def error(e):
    return redirect("http://wx.qq.com")

 
@app.route('/api', methods=['GET'])
def GetKey():
    key=request.args.get('t')
    key = key + "123456"
    if len(key) == 16:
        if not key:
            return redirect("http://wx.qq.com")
        else:
            resp = make_response(AES_Encrypt(key))
            resp.headers['server'] = 'stgw/1.3.12.4_1.13.5'
            return resp
    else:
        return redirect("http://wx.qq.com")


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=80, debug=False)
