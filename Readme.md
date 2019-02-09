# RadialWipe_s
[![MIT License](https://img.shields.io/packagist/l/doctrine/orm.svg)](LICENSE)
## ビルド

事前にシステムかユーザーの環境変数に`LUA_LIB_PATH`を作り、Luaのライブラリとヘッダファイルのパスを登録しておくと、後々楽です。  
そうでない場合は、プロジェクトのプロパティの`C/C++ -> General -> Additional Include Directories`の`$(LUA_LIB_PATH)`をLuaのヘッダのインクルードパスに、`Linker -> General -> Additional Library Directories`の`$(LUA_LIB_PATH)`をLuaのライブラリのパスにそれぞれ変更してください。  

その後、`General -> Output Directory`をDLLを出力したい場所に変更してください。  
自分のスクリプトのフォルダなどにしておくと、ビルドするたびにDLLをコピーしなくてもよくなるので少し楽になります。


## スクリプト内での呼び出し
このDLLの関数は、事前に`obj.getpixeldata()`の呼び出し等の前準備を必要としません。画像の取得などの下準備から処理後のデータの仕上げまですべてDLL内で完結しています。  
実際の呼び出しは、
```lua
require("RadialWipe_s")
RadialWipe_s.RadialWipe(sAngle, wAngle, xOffset, yOffset, fan)
```
のようになります。らくちん。


## 関数
このDLLモジュールに含まれている関数です。

```lua
RadialWipe(sAngle, wAngle, xOffset=0, yOffset=0, fan=false)
```
PixelSorterのメインの関数です。これを呼び出すとPixel Sortのエフェクトがかかった状態になります
#### 引数
必須
* `sAngle : float`  
	ワイプの開始角度
* `wAngle : float`  
	ワイプの角度
  
オプション
* `xOffset : float`  
	ワイプの中心位置からのオフセット(x)
* `yOffset : float`  
	ワイプの中心位置からのオフセット(y)
* `fan : bool`  
	左右両方にワイプするオプション