# gomisuteDisplay

# 概要
ゴミを捨てる前の日の夜に、『明日は何ゴミの日』であったかをストレスなく把握し、ゴミ捨ての準備を行いたい。
①『家庭ごみの正しい出し方』を参照して、今月のカレンダーと突き合わせて『明日のごみの種類』を特定する
②5374カレンダーのWEBサイトで確認する

# 問題点
①頭の中で計算がいる
②能動的にウェブサイトを閲覧しにいかなければならない
 ウェブサイトの表示が少し直感的ではない（個人的な感想です）
 ごみ捨ての準備時にウェブサイトを閲覧できる端末が手元にないとできない

# 特徴
- 家のゴミ捨て場の近くに設置することで、ゴミ捨て場に近づくときだけ閲覧が可能
- 人が近づいたときのみライトアップするため普段は主張しない
- 一番の関心ごとである『明日は何ゴミの日』が一番大きくアイコンで表示されるので直感的にわかりやすい
- 済マークを見ることで家族で共有可能
- web画面から、どの区分のゴミがどのくらいの頻度で出ているのかを把握できる

# 特徴
- 広島市南区段原の今日、明日および一週間のゴミ捨て区分が一目でわかる
- 

# やりたいこと(機能)

- [済]現在時刻が取得できていないのでntpなどで取得する
- [済]wifiのssidとpasswordはsdカードから書き換えれるようにしておき、本体の書き換えがいらないようにする。設定はjson?
- 内部の時計を持ち、日付が切り替わった時点で表示も切り替えるようにする
- 近くによった場合やボタンを押した場合に?秒間ライトを付ける
- この辺りは設定?
- ボタンを押して済にすると

# 表示に関して
- 基本的にはbrightnessは低くしておいて、どこかのボタンが押下されたら見えるようにする
- かっこの位置が変
- どこかのボタンに加えて超音波センサで近づいたら見えるようにする
- 表示が遅くてまどころっこしいので素早く表示できると良い
- 上と下に余白があったほうが良い。本日と明日のアイコンを小さくする？
- 