from urllib import request

with request.urlopen('https://api.github.com') as f:
    data = f.read()
    print(type(data))
