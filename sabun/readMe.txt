asset: 画像追加（texture/1st-4th,checkTutorial,Yes,No,pe\-0123,temporary(2)
		sound/BGM(title,Game,Result,)SE_POINTER）

main: #include sound Init,Uninit,Update(Include Soundはここだけで宣言するのでここ以外のsound.hを消す)

player:Play(Stop)Sound追加、isMobe追加（チュートリアル用）

各Scene: シーン遷移にisRelease 使用。ここはどうでもよいけど、一応


Scene:Tutorial追加。

title:チュートリアルの可否確認追加。それのための各bool追加

Game:ＢＧＭ追加
Result:シーン遷移追加

texture:追加した画像のラベル、α値いじれるTexture_Draw追加

sound:音楽のラベルと音声調整関数追加
