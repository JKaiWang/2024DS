from Crypto.Cipher import AES
import base64
import string

def aes_decrypt(cipher_text, key, iv="0000000000000000"):
    # Base64 解碼密文
    encrypted_data = base64.b64decode(cipher_text)
    # 建立 AES 解密器
    cipher = AES.new(key.encode('utf-8'), AES.MODE_CBC, iv.encode('utf-8'))
    # 解密並去除 Zero Padding
    decrypted_data = cipher.decrypt(encrypted_data)
    decrypted_data = decrypted_data.rstrip(b'\x00')
    # 將解密後的資料轉為 UTF-8 字串
    try:
        return decrypted_data.decode('utf-8')
    except UnicodeDecodeError:
        return None

# 密文與遮蔽金鑰的部分
cipher_text = "2mfH5wwaQuC9qvrfFPMgvIvU1ggfGcg8jkanFZfn91k="
key_template = "@K▆X%▆3Qh▆DD▆RqQ"

# 限定遮蔽部分為英文字母
possible_chars = string.ascii_letters

# 生成可能的金鑰
for ch1 in possible_chars:
    for ch2 in possible_chars:
        for ch3 in possible_chars:
            for ch4 in possible_chars:
                # 將方框替換為字母
                key = key_template.replace("▆", ch1, 1).replace("▆", ch2, 1).replace("▆", ch3, 1).replace("▆", ch4, 1)
                plaintext = aes_decrypt(cipher_text, key)
                if plaintext and plaintext[0].isalpha():  # 檢查解密結果是否以字母開頭
                    print(f"找到的最有可能的解密金鑰: {key}")
                    print(f"解密結果: {plaintext}")
                    exit()
