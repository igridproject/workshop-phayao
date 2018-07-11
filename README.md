# IoT Workshop @ Phayao

## Configulation
```
Control API :: http://phayao.bs.igridproject.info/api
Storage API :: http://phayao.bs.igridproject.info/api
```
Token :: Generate at -> [http://phayao.bs.igridproject.info/token](http://phayao.bs.igridproject.info/token)

## HTTP Push Channel
* URL Pattern :: http://phayao.bs.igridproject.info/io/<vo_name>.<appKey>
* Example
```
Send msg=hello,name=kamron to vo example and appKey ex01 
GET :: http://phayao.bs.igridproject.info/io/example.ex01?msg=hello&name=kamron
```