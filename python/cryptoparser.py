import fileinput
import json

class InvalidHeader(Exception):
    pass

class HeaderLogger:
    unsafe_URL_b64 = ['+', '/']
    def parse_header(self, header_value):
        res = []
        segments = header_value.split(',')
        for segment in segments:
            dict = {}
            key_val_pairs = segment.split(';')
            for keyVal in key_val_pairs:
                pos = keyVal.find('=')
                if pos == -1:
                    raise InvalidHeader("Key value pair {} is not '=' separated".format(keyVal))

                key = keyVal[0:pos]
                val = keyVal[pos+1:]
                if key =="" or val == "":
                    raise InvalidHeader("Missing Key or missing value in pair {}".format(keyVal))
                elif key == "keyid" and len(val.split()) > 1:
                    raise InvalidHeader("Key {} does not have single word value. Value is '{}'".format(key, val))

                key = self.unquote(key, True)
                val= self.unquote(val, False)

                # check URL safe base64
                for unsafe_char in self.unsafe_URL_b64:
                    if val.find(unsafe_char) != -1:
                        raise InvalidHeader("Val {} contains unsafe URL b64 char {}".format(val, unsafe_char))

                # strip any leading/trailing whitespace after a ',' or ';'
                key = key.strip(' ')
                val = val.strip(' ')

                key = self.strip_new_line(key)
                val = self.strip_new_line(val)
                dict[key] = val

            if len(dict) == 0:
                raise InvalidHeader("Empty header segment")

            res.append(dict)
        return res

    def strip_new_line(self, s):
        res = ""
        while len(s) > 0:
            pos = s.find('\n')
            if pos == -1:
                res += s
                break

            res += s[:pos]
            # strip repeating newline(s) and repeating spaces
            s = s.lstrip('\n')
            s = s.lstrip(' ')
        return res

    def unquote(self, text, isKey):
        quote = '"'
        if text.startswith(quote) and text.endswith(quote):
            return text[1:-1]
        elif text.startswith(quote) or text.endswith(quote):
            msg = ""
            if isKey:
                msg = "Key "
            else:
                msg = "Val "

            msg += "{} is improperly quoted".format(text)
            raise InvalidHeader(msg)
        else:
            return text

if __name__ == "__main__":
    parser = HeaderLogger()
    #parser.parse_header("keyid=p256dh fsdfsd; \n dh=AAA= ,\n p256ecdsa=AQ ; foo=\"bar=\";a=")
    #parser.parse_header("keyid=p256dh; \n dh=AAA= ,\n p256ecdsa=AQ ; foo=\"bar=\"")
    #res = parser.parse_header("keyid=p256dh; \n dh=AAA= ,\n p256ecdsa=AQ ; foo=bar=\"")
    #res = parser.parse_header("keyid=p256dh; \n dh=AAA= ,\n p256ecdsa=AQ ; foo=\"bar=\"")
    # res = parser.parse_header("keyid=p256dh; dh=  \n  AAA= ,\n p256ecdsa=AQ ; foo=\"bar=\";a")
    #res = parser.parse_header("keyid=p256dh; dh=  \n  AAA= ,\n p256ecdsa=AQ ; foo=\"bar=\";=")
    #res = parser.parse_header("keyid=p256dh; dh=  \n  AAA= ,\n p256ecdsa=AQ ; foo=\"bar=\";=")
    #res = parser.parse_header("keyid=p256dh; dh=  \n  AAA= ,\n p256ecdsa=AQ ; foo=\"bar=\"")
    #res = parser.parse_header("keyid=p256dh; dh=  \n  AAA= ,\n p256ecdsa=a/b ; foo=\"bar=\"")
    res = parser.parse_header("keyid=p256dh; dh=  \n  AAA= ,p256ecdsa=abc ; foo=\"bar=\"")
    print res


