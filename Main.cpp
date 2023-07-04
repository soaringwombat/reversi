# include <Siv3D.hpp> // OpenSiv3D v0.6.10

std::vector<std::vector<int>> status(8, std::vector<int>(8));	//マスの状態:0.なし，1.黒，2.白

//盤上のマス目，背景などの設定
void setup() {

	// 背景色を設定
	Scene::SetBackground(ColorF{ 1.0, 0.8, 1.0 });

	//盤を描写
	Rect{ 150, 50, 505, 505 }.draw(Palette::Lime);

	// 中心座標 (400, 300), 半径 20 の円を描く
	Circle{ Cursor::Pos(), 50 }.draw(Palette::Green);

	//盤上のマス目の描写
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Circle{ 182 + i * 63, 82 + j * 63,30 }.drawFrame(1, Palette::Black);
		}
	}
}

void Main()
{
	int x = 0;
	int y = 0;
	bool color = true;	//true.黒，false.白
	bool end_flag = false; //ゲームオーバーを確認

	// 基本サイズ 30 のフォントを作成
	const Font font{ 30 };

	const double hue = (Scene::Time() * 60);

	//初期配置の設定
	status.at(3).at(3) = 1;
	status.at(4).at(4) = 1;
	status.at(3).at(4) = 2;
	status.at(4).at(3) = 2;


	while (System::Update())
	{

		setup();

		//現在の状態をテキスト表示
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (status.at(i).at(j) == 0)	end_flag = true;
			}
		}
		if (end_flag && color) {
			font(U"黒色の番です．").draw(20, 5, Palette::Black);
		}
		else if (end_flag && !color) {
			font(U"白色の番です．").draw(20, 5, Palette::Black);
		}
		else {
			font(U"GAMEOVER").draw(20, 5, HSV{ hue, 0.6, 1.0 });

		}
		end_flag = false;

		//盤上の状態描写
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (status.at(i).at(j) == 0) {

				}
				else if (status.at(i).at(j) == 1) {
					Circle{ 182 + i * 63, 82 + j * 63,30 }.draw(Palette::Black);
				}
				else {
					Circle{ 182 + i * 63, 82 + j * 63,30 }.draw(Palette::White);
				}

			}
		}

		//選択マスの表示
		Circle{ 182 + x * 63, 82 + y * 63,30 }.drawFrame(5, Palette::Green);


		//マスの選択
		//右移動
		if (KeyRight.down()) {
			x = Min(x + 1, 7);
		}
		//左移動
		if (KeyLeft.down()) {
			x = Max(x - 1, 0);
		}
		//下移動
		if (KeyDown.down()) {
			y = Min(y + 1, 7);
		}
		//上移動
		if (KeyUp.down()) {
			y = Max(y - 1, 0);
		}

		//石を置く
		if (KeySpace.down()) {
			if (status.at(x).at(y) == 0) {
				if (color) {
					status.at(x).at(y) = 1;
				}
				else {
					status.at(x).at(y) = 2;
				}

				//ひっくり返すマスの確定
				int color_count = 0;	//はさんでいる相手の石をカウントする．

				//上方向
				for (int i = y - 1; i >= 0; i--) {
					//白の場合
					if (!color) {
						if (status.at(x).at(i) == 1) {
							color_count++;
						}
						else if (status.at(x).at(i) == 2) {
							for (int j = 0; j < color_count; j++) {
								status.at(x).at(y - j - 1) = 2;
							}
							break;
						}
						else {
							break;
						}
					}
					//黒の場合
					else {
						if (status.at(x).at(i) == 2) {
							color_count++;
						}
						else if (status.at(x).at(i) == 1) {
							for (int j = 0; j < color_count; j++) {
								status.at(x).at(y - j - 1) = 1;
							}
							break;
						}
						else {
							break;
						}
					}
				}

				color_count = 0;	//初期化
				//下方向
				for (int i = y + 1; i < 8; i++) {
					//白の場合
					if (!color) {
						if (status.at(x).at(i) == 1) {
							color_count++;
						}
						else if (status.at(x).at(i) == 2) {
							for (int j = 0; j < color_count; j++) {
								status.at(x).at(y + j + 1) = 2;
							}
							break;
						}
						else {
							break;
						}
					}
					//黒の場合
					else {
						if (status.at(x).at(i) == 2) {
							color_count++;
						}
						else if (status.at(x).at(i) == 1) {
							for (int j = 0; j < color_count; j++) {
								status.at(x).at(y + j + 1) = 1;
							}
							break;
						}
						else {
							break;
						}
					}
				}

				color_count = 0;	//初期化
				//右方向
				for (int i = x + 1; i < 8; i++) {
					//白の場合
					if (!color) {
						if (status.at(i).at(y) == 1) {
							color_count++;
						}
						else if (status.at(i).at(y) == 2) {
							for (int j = 0; j < color_count; j++) {
								status.at(x + j + 1).at(y) = 2;
							}
							break;
						}
						else {
							break;
						}
					}
					//黒の場合
					else {
						if (status.at(i).at(y) == 2) {
							color_count++;
						}
						else if (status.at(i).at(y) == 1) {
							for (int j = 0; j < color_count; j++) {
								status.at(x + j + 1).at(y) = 1;
							}
							break;
						}
						else {
							break;
						}
					}
				}

				color_count = 0;	//初期化
				//左方向
				for (int i = x - 1; i >= 0; i--) {
					//白の場合
					if (!color) {
						if (status.at(i).at(y) == 1) {
							color_count++;
						}
						else if (status.at(i).at(y) == 2) {
							for (int j = 0; j < color_count; j++) {
								status.at(x - j - 1).at(y) = 2;
							}
							break;
						}
						else {
							break;
						}
					}
					//黒の場合
					else {
						if (status.at(i).at(y) == 2) {
							color_count++;
						}
						else if (status.at(i).at(y) == 1) {
							for (int j = 0; j < color_count; j++) {
								status.at(x - j - 1).at(y) = 1;
							}
							break;
						}
						else {
							break;
						}
					}
				}

				color_count = 0;	//初期化
				//右上方向
				for (int i = 1; i < 8 - x && i < y + 1; i++) {
					//白の場合
					if (!color) {
						if (status.at(x + i).at(y - i) == 1) {
							color_count++;
						}
						else if (status.at(x + i).at(y - i) == 2) {
							for (int j = 0; j < color_count; j++) {
								status.at(x + j + 1).at(y - j - 1) = 2;
							}
							break;
						}
						else {
							break;
						}
					}
					//黒の場合
					else {
						if (status.at(x + i).at(y - i) == 2) {
							color_count++;
						}
						else if (status.at(x + i).at(y - i) == 1) {
							for (int j = 0; j < color_count; j++) {
								status.at(x + j + 1).at(y - j - 1) = 1;
							}
							break;
						}
						else {
							break;
						}
					}
				}

				color_count = 0;	//初期化
				//右下方向
				for (int i = 1; i < 8 - x && i < 8 - y; i++) {
					//白の場合
					if (!color) {
						if (status.at(x + i).at(y + i) == 1) {
							color_count++;
						}
						else if (status.at(x + i).at(y + i) == 2) {
							for (int j = 0; j < color_count; j++) {
								status.at(x + j + 1).at(y + j + 1) = 2;
							}
							break;
						}
						else {
							break;
						}
					}
					//黒の場合
					else {
						if (status.at(x + i).at(y + i) == 2) {
							color_count++;
						}
						else if (status.at(x + i).at(y + i) == 1) {
							for (int j = 0; j < color_count; j++) {
								status.at(x + j + 1).at(y + j + 1) = 1;
							}
							break;
						}
						else {
							break;
						}
					}
				}

				color_count = 0;	//初期化
				//左下方向
				for (int i = 1; i < x + 1 && i < 8 - y; i++) {
					//白の場合
					if (!color) {
						if (status.at(x - i).at(y + i) == 1) {
							color_count++;
						}
						else if (status.at(x - i).at(y + i) == 2) {
							for (int j = 0; j < color_count; j++) {
								status.at(x - j - 1).at(y + j + 1) = 2;
							}
							break;
						}
						else {
							break;
						}
					}
					//黒の場合
					else {
						if (status.at(x - i).at(y + i) == 2) {
							color_count++;
						}
						else if (status.at(x - i).at(y + i) == 1) {
							for (int j = 0; j < color_count; j++) {
								status.at(x - j - 1).at(y + j + 1) = 1;
							}
							break;
						}
						else {
							break;
						}
					}
				}

				color_count = 0;	//初期化
				//左上方向
				for (int i = 1; i < x + 1 && i < y + 1; i++) {
					//白の場合
					if (!color) {
						if (status.at(x - i).at(y - i) == 1) {
							color_count++;
						}
						else if (status.at(x - i).at(y - i) == 2) {
							for (int j = 0; j < color_count; j++) {
								status.at(x - j - 1).at(y - j - 1) = 2;
							}
							break;
						}
						else {
							break;
						}
					}
					//黒の場合
					else {
						if (status.at(x - i).at(y - i) == 2) {
							color_count++;
						}
						else if (status.at(x - i).at(y - i) == 1) {
							for (int j = 0; j < color_count; j++) {
								status.at(x - j - 1).at(y - j - 1) = 1;
							}
							break;
						}
						else {
							break;
						}
					}
				}

				color = !color;	//相手のターンへ移行
			}
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
