# RadialWipe_s
[![MIT License](https://img.shields.io/packagist/l/doctrine/orm.svg)](LICENSE)
## ビルド

`build`ディレクトリを作成してターミナルで入り、cmake_batch.sh内の`lua_include_dir`、`lua_library_dir`と`cmake_install_path`にそれぞれのパスを追加し、
```sh
../cmake_batch.sh msvc
```
でプロジェクトが生成されます。そのまま
```sh
../msvc_build.sh install
```
で`cmake_install_path`に指定したディレクトリにDLLとanmファイルが配置されます。  
`install`の代わりに`build`や`rebuild`も指定できます。


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
RadialWipeのメインの関数です。これを呼び出すとRadialWipeエフェクトがかかった状態になります
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


```lua
RadialBlind(progress, sOffset, division, xOffset=0, yOffset=0, fan=false, clockWise=true)
```
所謂扇ブラインドのエフェクトをかける関数です。これを呼び出すとRadialBlindエフェクトがかかった状態になります
#### 引数
必須
* `progress : float`  
	ブラインドの割合(-100~100%)
* `sOffset : float`  
	ブラインドのオフセットの角度
  
オプション
* `xOffset : float`  
	ブラインドの中心位置からのオフセット(x)
* `yOffset : float`  
	ブラインドの中心位置からのオフセット(y)
* `fan : bool`  
	左右両方にブラインドを広げるオプション
* `clockWise : bool`  
	時計回りにブラインドを展開するオプション  
	falseにすると反時計回りになる