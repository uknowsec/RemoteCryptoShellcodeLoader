# coding=utf-8
from flask import jsonify
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
    text = 'xxxx'   
    cipher = AES.new(key.encode('utf8'), AES.MODE_CBC, vi.encode('utf8'))

    encrypted = cipher.encrypt(pad(text)).encode('hex')
    return str(encrypted)


@app.errorhandler(404)
def miss(e):
    return redirect("http://baidu.com")
 
@app.errorhandler(500)
def error(e):
    return redirect("http://baidu.com")

 
@app.route('/api', methods=['GET'])
def GetKey():
    key=request.args.get('t')
    key = key + "123456"
    if len(key) == 16:
        if not key:
            return redirect("http://baidu.com")
        else:
            resp = make_response(AES_Encrypt(key))
            resp.headers['server'] = 'stgw/1.3.12.4_1.13.5'
            return resp
    else:
        return redirect("http://baidu.com")


if __name__ == '__main__':
    app.run(host="0.0.0.0", port=23333, debug=False)
