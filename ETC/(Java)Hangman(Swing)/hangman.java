import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import javax.swing.*;
import java.io.*;


/* <applet code="hangman" width="800"  height="600">
</applet> */

public class hangman extends JFrame implements ActionListener {
	String[] words = new String[201];
	String check_word;
	String[] word2 = new String[12];
	char[] word1 = new char[12];
	
	int guessNum;
	int level;
	int[] check = new int[201];
	
	
	JButton a = new JButton("A");	JButton b = new JButton("B");	JButton c = new JButton("C");
	JButton d = new JButton("D");	JButton e = new JButton("E");	JButton f = new JButton("F");
	JButton g = new JButton("G");	JButton h = new JButton("H");	JButton i = new JButton("I");
	JButton j = new JButton("J");	JButton k = new JButton("K");	JButton l = new JButton("L");
	JButton m = new JButton("M");	JButton n = new JButton("N");	JButton o = new JButton("O");
	JButton p = new JButton("P");	JButton q = new JButton("Q");	JButton r = new JButton("R");
	JButton s = new JButton("S");	JButton t = new JButton("T");	JButton u = new JButton("U");
	JButton v = new JButton("V");	JButton w = new JButton("W");	JButton x = new JButton("X");
	JButton y = new JButton("Y");	JButton z = new JButton("Z");	

	JButton begin = new JButton("BEGIN");
	JButton easy = new JButton("EASY");	JButton medium = new JButton("MEDIUM");	JButton hard = new JButton("HARD");
	JButton hint = new JButton("HINT");
	JButton nhint = new JButton("NOT_HINT");
	int n_hint=0;
	JLabel text = new JLabel("Skill level: ", JLabel.LEFT);

	JPanel finalDisplay = new JPanel();
	JPanel display1 = new JPanel();  	
	JPanel display2 = new JPanel();
	
	
	Font normalFont = new Font("Arial", Font.BOLD, 16);
	Font warningFont = new Font("Arial", Font.BOLD, 20);
	

	int gameNo = 0;			// 게임횟수
	int win = 0; 			//성공횟수
	int lose = 0; 			//실패횟수
	double win_percent;		// 승률
	String str_level = "EASY";		// 레벨 표시 스트링
	
	public void main(String[] args){
		hangman hm = new hangman();
	}
	public hangman() {
		
		for(int i=0; i<check.length;i++)
			check[i] = 0;
		
		
		a.addActionListener(this);		b.addActionListener(this);		c.addActionListener(this);
		d.addActionListener(this);		e.addActionListener(this);		f.addActionListener(this);
		g.addActionListener(this);		h.addActionListener(this);		i.addActionListener(this);
		j.addActionListener(this);		k.addActionListener(this);		l.addActionListener(this);
		m.addActionListener(this);		n.addActionListener(this);		o.addActionListener(this);
		p.addActionListener(this);		q.addActionListener(this);		r.addActionListener(this);
		s.addActionListener(this);		t.addActionListener(this);		u.addActionListener(this);
		v.addActionListener(this);		w.addActionListener(this);		x.addActionListener(this);
		y.addActionListener(this);		z.addActionListener(this);

		begin.addActionListener(this);
		hint.addActionListener(this);
		nhint.addActionListener(this);
		
		easy.addActionListener(this);		medium.addActionListener(this);		hard.addActionListener(this);
		
		GridLayout all = new GridLayout(3,1,20,60);  // 전체 panel에 대한 layout 설정
		FlowLayout bbb = new FlowLayout(FlowLayout.CENTER);  // finalDisplay에 대한 layout
		FlowLayout ccc = new FlowLayout(FlowLayout.CENTER);  // display2에 대한 layout
		GridLayout ddd = new GridLayout(4,6,5,5);  // display1에 대한 layout
		
		Container root = getContentPane();
		root.setLayout(all);
		root.setBackground(Color.white);

		finalDisplay.setLayout(bbb);
		finalDisplay.setBackground(Color.white);
		finalDisplay.add(begin);
		finalDisplay.add(hint);
		finalDisplay.add(nhint);
		root.add(finalDisplay);
		display1.setLayout(ddd);
		display1.setBackground(Color.white);

		a.setBackground(Color.orange);		b.setBackground(Color.orange);		c.setBackground(Color.orange);
		d.setBackground(Color.orange);		e.setBackground(Color.orange);		f.setBackground(Color.orange);
		g.setBackground(Color.orange);		h.setBackground(Color.orange);		i.setBackground(Color.orange);
		j.setBackground(Color.orange);		k.setBackground(Color.orange);		l.setBackground(Color.orange);
		m.setBackground(Color.orange);		n.setBackground(Color.orange);		o.setBackground(Color.orange);
		p.setBackground(Color.orange);		q.setBackground(Color.orange);		r.setBackground(Color.orange);
		s.setBackground(Color.orange);		t.setBackground(Color.orange);		u.setBackground(Color.orange);
		v.setBackground(Color.orange);		w.setBackground(Color.orange);		x.setBackground(Color.orange);
		y.setBackground(Color.orange);		z.setBackground(Color.orange);
		
		display1.add(a);		display1.add(b);		display1.add(c);		display1.add(d);
		display1.add(e);		display1.add(f);		display1.add(g);		display1.add(h);
		display1.add(i);		display1.add(j);		display1.add(k);		display1.add(l);
		display1.add(m);		display1.add(n);		display1.add(o);		display1.add(p);
		display1.add(q);		display1.add(r);		display1.add(s);		display1.add(t);
		display1.add(u);		display1.add(v);		display1.add(w);		display1.add(x);
		display1.add(y);		display1.add(z);

		root.add(display1);
		display2.setLayout(ccc);
		display2.setBackground(Color.white);
		display2.add(text);
		display2.add(easy);
		display2.add(medium);
		display2.add(hard);

		root.add(display2);
		setContentPane(root);
		a.setEnabled(false);		b.setEnabled(false);		c.setEnabled(false);		d.setEnabled(false);
		e.setEnabled(false);		f.setEnabled(false);		g.setEnabled(false);		h.setEnabled(false);
		i.setEnabled(false);		j.setEnabled(false);		k.setEnabled(false);		l.setEnabled(false);
		m.setEnabled(false);		n.setEnabled(false);		o.setEnabled(false);		p.setEnabled(false);
		q.setEnabled(false);		r.setEnabled(false);		s.setEnabled(false);		t.setEnabled(false);
		u.setEnabled(false);		v.setEnabled(false);		w.setEnabled(false);		x.setEnabled(false);
		y.setEnabled(false);		z.setEnabled(false);
		
		easy.setEnabled(false);
		hint.setEnabled(true);
		nhint.setEnabled(false);
		n_hint = 0;

		level = 0;
		
		words[0] = "korea";
		words[1] = "compile";
		words[2] = "dictionary";
		words[3] = "apple";
		words[4] = "banana";
		words[5] = "america";
		words[6] = "university";
		words[7] = "computer";
		words[8] = "power";
		words[9] = "small";
		words[10] = "total";
		words[11] = "magic";
		words[12] = "secret";
		words[13] = "generation";
		words[14] = "special";
		words[15] = "filter";
		words[16] = "water";
		words[17] = "milk";
		words[18] = "point";
		words[19] = "diagram";
		words[20] = "normal";
		words[21] = "make";
		words[22] = "sports";
		words[23] = "window";
		words[24] = "style";
		words[25] = "black";
		words[26] = "white";
		words[27] = "green";
		words[28] = "pencil";
		words[29] = "panda";
		words[30] = "cold";
		words[31] = "battery";
		words[32] = "smart";
		words[33] = "telephone";
		words[34] = "network";
		words[35] = "game";
		words[36] = "football";
		words[37] = "basketball";
		words[38] = "golf";
		words[39] = "drive";
		words[40] = "double";
		words[41] = "float";
		words[42] = "island";
		words[43] = "terminal";
		words[44] = "advance";
		words[45] = "flight";
		words[46] = "fight";
		words[47] = "foul";
		words[48] = "strike";
		words[49] = "catch";
		words[50] = "swim";
		words[51] = "crawl";
		words[52] = "hand";
		words[53] = "foot";
		words[54] = "center";
		words[55] = "shadow";
		words[56] = "back";
		words[57] = "bone";
		words[58] = "head";
		words[59] = "finger";
		words[60] = "gold";
		words[61] = "queen";
		words[62] = "rich";
		words[63] = "diamond";
		words[64] = "story";
		words[65] = "brew";
		words[66] = "wine";
		words[67] = "cream";
		words[68] = "cheese";
		words[69] = "monitor";
		words[70] = "decate";
		words[71] = "grape";
		words[72] = "glass";
		words[73] = "data";
		words[74] = "struct";
		words[75] = "wind";
		words[76] = "fire";
		words[77] = "earth";
		words[78] = "alchol";
		words[79] = "pressure";
		words[80] = "air";
		words[81] = "dust";
		words[82] = "fowder";
		words[83] = "bacteria";
		words[84] = "restaurent";
		words[85] = "frog";
		words[86] = "meet";
		words[87] = "meat";
		words[88] = "fruit";
		words[89] = "cloud";
		words[90] = "soldier";
		words[91] = "metal";
		words[92] = "golem";
		words[93] = "flower";
		words[94] = "tree";
		words[95] = "butterfly";
		words[96] = "farmer";
		words[97] = "thunder";
		words[98] = "swarmp";
		words[99] = "egg";
		words[100] = "snail";
		words[101] = "chicken";
		words[102] = "lizard";
		words[103] = "poison";
		words[104] = "stone";
		words[105] = "beetle";
		words[106] = "dust";
		words[107] = "sand";
		words[108] = "clock";
		words[109] = "weapon";
		words[110] = "fish";
		words[111] = "tire";
		words[112] = "snake";
		words[113] = "mushroom";
		words[114] = "worm";
		words[115] = "boat";
		words[116] = "plan";
		words[117] = "light";
		words[118] = "darkness";
		words[119] = "bread";
		words[120] = "hunter";
		words[121] = "love";
		words[123] = "human";
		words[124] = "desert";
		words[125] = "bird";
		words[126] = "life";
		words[127] = "oxygen";
		words[128] = "diet";
		words[129] = "feed";
		words[130] = "aluminum";
		words[131] = "energy";
		words[132] = "hero";
		words[133] = "suit";
		words[134] = "yogurt";
		words[135] = "dragon";
		words[136] = "lava";
		words[137] = "ghost";
		words[138] = "electric";
		words[139] = "pearl";
		words[140] = "beast";
		words[141] = "toast";
		words[142] = "explosion";
		words[143] = "strom";
		words[144] = "blood";
		words[145] = "pizza";
		words[146] = "volacano";
		words[147] = "beach";
		words[148] = "alien";
		words[149] = "ambulance";
		words[150] = "arms";
		words[151] = "barbecue";
		words[152] = "bear";
		words[153] = "beaver";
		words[154] = "berry";
		words[155] = "book";
		words[156] = "brick";
		words[157] = "camel";
		words[158] = "cart";
		words[159] = "ceramic";
		words[160] = "boiler";
		words[161] = "city";
		words[162] = "cloth";
		words[163] = "cocoa";
		words[164] = "dinosaur";
		words[165] = "doctor";
		words[166] = "dough";
		words[167] = "donut";
		words[168] = "feather";
		words[169] = "firefly";
		words[170] = "grass";
		words[171] = "grove";
		words[172] = "idea";
		words[173] = "hospital";
		words[174] = "honey";
		words[175] = "juice";
		words[176] = "lamp";
		words[177] = "mirror";
		words[178] = "money";
		words[179] = "moon";
		words[180] = "mouse";
		words[181] = "museum";
		words[182] = "penguin";
		words[183] = "rust";
		words[184] = "prison";
		words[185] = "braek";
		words[186] = "sandwich";
		words[187] = "scientist";
		words[188] = "seed";
		words[189] = "shells";
		words[190] = "star";
		words[191] = "sugar";
		words[192] = "stake";
		words[193] = "team";
		words[194] = "project";
		words[195] = "time";
		words[196] = "whale";
		words[197] = "wolf";
		words[198] = "wheel";
		words[199] = "fortune";
		words[200] = "drink";	
		

		addWindowListener(new WindowEventHandler());
		setSize(800,600);
		setVisible(true);
		word_reset();
	}

	public void paint(Graphics screen) {
		super.paint(screen);
		Graphics2D screen2D = (Graphics2D) screen;
		screen2D.setFont(normalFont);

		screen2D.drawString("Wins " + win + "     Looses " + lose + "      WinnigProsentige " + win_percent + "%", 230,160);
		screen2D.drawString("Current skill level: " + str_level, 320,180);

		for(int i = 0; i < 12 ; i++){		// 정답 화면에 표시
			if(word2[i] != "."){
				screen2D.drawString(word2[i], 100+40*i, 115);

			}
		}

		for(int i = 0; i < 12; i++){		// 밑줄
			if(word1[i] != ' '){
				screen2D.drawLine(100 + 40*i, 122, 108 + 40*i,122);
				screen2D.drawLine(100 + 40*i, 123, 108 + 40*i,123);
			}
		}

		screen2D.setColor(Color.red);
		screen2D.setFont(warningFont);
		screen2D.drawString(guessNum + " guesses left",340,200);

		
		
		screen2D.setColor(Color.black);

		screen2D.drawLine(650,50,650,220);
		screen2D.drawLine(650,185,635,210);
		screen2D.drawLine(650,185,610,220);
		screen2D.drawLine(650,185,665,210);
		screen2D.drawLine(650,185,690,220);
		screen2D.drawLine(620,50,760,50);
		screen2D.drawLine(650,80,690,50);
		screen2D.drawLine(750,50,750,90);
		
		if(level == 0){			//easy 사람그리기
			if(guessNum == 9){
				screen2D.drawArc(710,70,38,38,90,180);
			}else if(guessNum == 8){
				screen2D.drawOval(710,70,38,38);
			}else if(guessNum == 7){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,110);
			}else if(guessNum == 6){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,130);
			}else if(guessNum == 5){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,145);
			}else if(guessNum == 4){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
			}else if(guessNum == 3){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
			}else if(guessNum == 2){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
				screen2D.drawLine(750,100,760,155);
			}else if(guessNum == 1){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,160,745,205);
			}else if(guessNum == 0){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,160,745,205);
				screen2D.drawLine(750,160,757,215);
				screen2D.setColor(Color.red);
				screen2D.setFont(warningFont);
				screen2D.drawString("GameOver", 640, 130);
			}

		}
	
		if(level == 1){			//medium 사람그리기
			if(guessNum == 7){
				screen2D.drawArc(710,70,38,38,90,180);
			}else if(guessNum == 6){
				screen2D.drawOval(710,70,38,38);
			}else if(guessNum == 5){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,115);
			}else if(guessNum == 4){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
			}else if(guessNum == 3){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
			}else if(guessNum == 2){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
				screen2D.drawLine(750,100,760,155);
			}else if(guessNum == 1){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,160,745,205);
			}else if(guessNum == 0){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,160,745,205);
				screen2D.drawLine(750,160,757,215);
				screen2D.setColor(Color.red);
				screen2D.setFont(warningFont);
				screen2D.drawString("GameOver", 640, 130);
			}

		}

		if(level == 2){			//hard 사람그리기
			if(guessNum == 5){
				screen2D.drawOval(710,70,38,38);
			}else if(guessNum == 4){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
			}else if(guessNum == 3){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
			}else if(guessNum == 2){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
				screen2D.drawLine(750,100,760,155);
			}else if(guessNum == 1){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,160,745,205);
			}else if(guessNum == 0){
				screen2D.drawOval(710,70,38,38);
				screen2D.drawLine(750,93,750,160);
				screen2D.drawLine(750,100,745,138);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,100,760,155);
				screen2D.drawLine(750,160,745,205);
				screen2D.drawLine(750,160,757,215);
				screen2D.setColor(Color.red);
				screen2D.setFont(warningFont);
				screen2D.drawString("GameOver", 640, 130);
			}

		}
	}
	int word_length;
	String sel_Word;

	public void wordSelect() {
		double sel_num = Math.random() * 201;
		int selection = (int) Math.floor(sel_num);
//		int word_length;
//		String sel_Word;

		if(check[selection] == 0){
			if(words[selection] != null){
				sel_Word = words[selection].toLowerCase();
				word_length = sel_Word.length();
			
				char[] temp = sel_Word.toCharArray();
					for(int index1 = 0; index1 < word_length; index1++){
						word1[index1] = temp[index1];
					}
					for(int index2 = word_length; index2 < 12; index2++){
						word2[index2] = ".";
					}
				check[selection] = 1;
			}
		}
		else if(check[selection] == 1){
			wordSelect();
		}
	}

	public void word_reset() {
		for(int i=0; i<=11;i++){
			word1[i] = ' ';
			word2[i] ="";
		}
		wordSelect();
	}

	public void spell_check(char spell) {
		int check_key = 0;
		for(int i = 0; i < 12; i++){
			if(word1[i] != ' '){
				if(word1[i] == spell){
					word2[i] = "" + spell;
					check_key = 1;
					repaint();
				}
			}
		}
		if(check_key == 0) {
			guessNum--;
			repaint();
		}
		Adjust_display();
		repaint();
	}

	public void Adjust_display() {
		int word_length = word1.length;
		
		if(word_length == 4){
			if(word2[0] != "" & word2[1] != "" & word2[2] != "" & word2[3] != ""){
				ab_false();
				begin.setEnabled(true);
				difficulty_button_true();
				win++;
				gameNo++;
				win_percent = ((double)win / (double)gameNo) * 100;
				repaint();
			}
		}
		if(word_length == 5){
			if(word2[0] != "" & word2[1] != "" & word2[2] != "" & word2[3] != "" & word2[4] != ""){
				ab_false();
				begin.setEnabled(true);
				difficulty_button_true();
				win++;
				gameNo++;
				win_percent = ((double)win / (double)gameNo) * 100;
				repaint();
			}
		}
		if(word_length == 6){
			if(word2[0] != "" & word2[1] != "" & word2[2] != "" & word2[3] != "" & word2[4] != "" & word2[5] != ""){
				ab_false();
				begin.setEnabled(true);
				difficulty_button_true();
				win++;
				gameNo++;
				win_percent = ((double)win / (double)gameNo) * 100;
				repaint();
			}
		}
		if(word_length == 7){
			if(word2[0] != "" & word2[1] != "" & word2[2] != "" & word2[3] != "" & word2[4] != "" & word2[5] != "" & word2[6] != ""){
				ab_false();
				begin.setEnabled(true);
				difficulty_button_true();
				win++;
				gameNo++;
				win_percent = ((double)win / (double)gameNo) * 100;
				repaint();
			}
		}
		if(word_length == 8){
			if(word2[0] != "" & word2[1] != "" & word2[2] != "" & word2[3] != "" & word2[4] != "" & word2[5] != "" & word2[6] != "" & word2[7] != ""){
				ab_false();
				begin.setEnabled(true);
				difficulty_button_true();
				win++;
				gameNo++;
				win_percent = ((double)win / (double)gameNo) * 100;
				repaint();
			}
		}
		if(word_length == 9){
			if(word2[0] != "" & word2[1] != "" & word2[2] != "" & word2[3] != "" & word2[4] != "" & word2[5] != "" & word2[6] != "" & word2[7] != "" & word2[8] != ""){
				ab_false();
				begin.setEnabled(true);
				difficulty_button_true();
				win++;
				gameNo++;
				win_percent = ((double)win / (double)gameNo) * 100;
				repaint();
			}
		}
		if(word_length == 10){
			if(word2[0] != "" & word2[1] != "" & word2[2] != "" & word2[3] != "" & word2[4] != "" & word2[5] != "" & word2[6] != "" & word2[7] != "" & word2[8] != "" & word2[9] != ""){
				ab_false();
				begin.setEnabled(true);
				difficulty_button_true();
				win++;
				gameNo++;
				win_percent = ((double)win / (double)gameNo) * 100;
				repaint();
			}
		}
		if(word_length == 11){
			if(word2[0] != "" & word2[1] != "" & word2[2] != "" & word2[3] != "" & word2[4] != "" & word2[5] != "" & word2[6] != "" & word2[7] != "" & word2[8] != "" & word2[9] != "" & word2[10] != ""){

				ab_false();
				begin.setEnabled(true);
				difficulty_button_true();
				win++;
				gameNo++;
				win_percent = ((double)win / (double)gameNo) * 100;
				repaint();
			}
		}
		if(word_length == 12){
			if(word2[0] != "" & word2[1] != "" & word2[2] != "" & word2[3] != "" & word2[4] != "" & word2[5] != "" & word2[6] != "" & word2[7] != "" & word2[8] != "" & word2[9] != "" & word2[10] != "" & word2[11] != ""){
				ab_false();
				begin.setEnabled(true);
				difficulty_button_true();
				win++;
				gameNo++;
				win_percent = ((double)win / (double)gameNo) * 100;
				repaint();
			}
		}
		if(guessNum <= 0){
			ab_false();
			for(int j = 0; j < 12; j++)	word2[j] = "" + word1[j];
			begin.setEnabled(true);
			difficulty_button_true();
			lose++;
			gameNo++;
			win_percent = ((double)win / (double)gameNo) * 100;
			repaint();
		}
		if(guessNum <= 0) {  // 단어 추정 실패 
			a.setEnabled(false);  	z.setEnabled(false);
			word2[0] = "" + word1[0];  // 정답을 화면에 표시

                        word2[11] = "" + word1[11];
			begin.setEnabled(true);	
			/* level에 따른 버튼 활성화 작업 */
		}

	}

	public void ab_true(){
		a.setEnabled(true);		b.setEnabled(true);		c.setEnabled(true);
		d.setEnabled(true);		e.setEnabled(true);		f.setEnabled(true);
		g.setEnabled(true);		h.setEnabled(true);		i.setEnabled(true);
		j.setEnabled(true);		k.setEnabled(true);		l.setEnabled(true);
		m.setEnabled(true);		n.setEnabled(true);		o.setEnabled(true);
		p.setEnabled(true);		q.setEnabled(true);		r.setEnabled(true);
		s.setEnabled(true);		t.setEnabled(true);		u.setEnabled(true);
		v.setEnabled(true);		w.setEnabled(true);		x.setEnabled(true);
		y.setEnabled(true);		z.setEnabled(true);
	}
	
	public void ab_false(){
		a.setEnabled(false);		b.setEnabled(false);		c.setEnabled(false);
		d.setEnabled(false);		e.setEnabled(false);		f.setEnabled(false);
		g.setEnabled(false);		h.setEnabled(false);		i.setEnabled(false);
		j.setEnabled(false);		k.setEnabled(false);		l.setEnabled(false);
		m.setEnabled(false);		n.setEnabled(false);		o.setEnabled(false);
		p.setEnabled(false);		q.setEnabled(false);		r.setEnabled(false);
		s.setEnabled(false);		t.setEnabled(false);		u.setEnabled(false);
		v.setEnabled(false);		w.setEnabled(false);		x.setEnabled(false);
		y.setEnabled(false);		z.setEnabled(false);		
	}
	
	public void difficulty_button_true(){	// 레벨에 따른 난이도 버튼 활성화
		if(level == 0){
			medium.setEnabled(true);
			hard.setEnabled(true);
		} else if(level == 1){
			easy.setEnabled(true);
			hard.setEnabled(true);
		} else if(level == 2){
			medium.setEnabled(true);
			easy.setEnabled(true);
		}
}

	public void actionPerformed(ActionEvent event) {
		String typed = event.getActionCommand();
		if(typed.equals("HINT")){
				hint.setEnabled(false);
				nhint.setEnabled(true);
				n_hint =1;
		}
		if(typed.equals("NOT_HINT")){
			hint.setEnabled(true);
			nhint.setEnabled(false);
			n_hint=0;
		}
		if(typed.equals("BEGIN")) {
			word_reset();
			ab_true();
			begin.setEnabled(false);
			easy.setEnabled(false);
			medium.setEnabled(false);
			hard.setEnabled(false);

			if(level == 0) {
				guessNum = 10;
			} else if(level == 1) {
				guessNum = 8;
			} else if(level == 2) {
			guessNum = 6;
			}
			repaint();
			
			if(n_hint ==1 && word_length >=6){
				char hin = word1[word_length-1];
				spell_check(hin);
			}
	
				
		}
		
		if(typed.equals("EASY")) {
			easy.setEnabled(false);
			medium.setEnabled(true);
			hard.setEnabled(true);
			level = 0;
			str_level = "EASY";
			repaint();
		}
		if(typed.equals("MEDIUM")) {
			medium.setEnabled(false);
			hard.setEnabled(true);
			easy.setEnabled(true);
			level = 1;
			str_level = "MEDIUM";
			repaint();
		}
		if(typed.equals("HARD")) {
			hard.setEnabled(false);
			medium.setEnabled(true);
			easy.setEnabled(true);
			str_level = "HARD";
			level = 2;
			repaint();
		}

		if(typed.equals("A")) {
			a.setEnabled(false);
			spell_check('a');
		}

		if(typed.equals("B")) {
			b.setEnabled(false);
			spell_check('b');
		}

		if(typed.equals("C")) {
			c.setEnabled(false);
			spell_check('c');
		}

		if(typed.equals("D")) {
			d.setEnabled(false);
			spell_check('d');
		}

		if(typed.equals("E")) {
			e.setEnabled(false);
			spell_check('e');
		}

		if(typed.equals("F")) {
			f.setEnabled(false);
			spell_check('f');
		}

		if(typed.equals("G")) {
			g.setEnabled(false);
			spell_check('g');
		}

		if(typed.equals("H")) {
			h.setEnabled(false);
			spell_check('h');
		}

		if(typed.equals("I")) {
			i.setEnabled(false);
			spell_check('i');
		}

		if(typed.equals("J")) {
			j.setEnabled(false);
			spell_check('j');
		}

		if(typed.equals("K")) {
			k.setEnabled(false);
			spell_check('k');
		}

		if(typed.equals("L")) {
			l.setEnabled(false);
			spell_check('l');
		}

		if(typed.equals("M")) {
			m.setEnabled(false);
			spell_check('m');
		}

		if(typed.equals("N")) {
			n.setEnabled(false);
			spell_check('n');
		}

		if(typed.equals("O")) {
			o.setEnabled(false);
			spell_check('o');
		}

		if(typed.equals("P")) {
			p.setEnabled(false);
			spell_check('p');
		}

		if(typed.equals("Q")) {
			q.setEnabled(false);
			spell_check('q');
		}

		if(typed.equals("R")) {
			r.setEnabled(false);
			spell_check('r');
		}

		if(typed.equals("S")) {
			s.setEnabled(false);
			spell_check('s');
		}

		if(typed.equals("T")) {
			t.setEnabled(false);
			spell_check('t');
		}

		if(typed.equals("U")) {
			u.setEnabled(false);
			spell_check('u');
		}

		if(typed.equals("V")) {
			v.setEnabled(false);
			spell_check('v');
		}

		if(typed.equals("W")) {
			w.setEnabled(false);
			spell_check('w');
		}

		if(typed.equals("X")) {
			x.setEnabled(false);
			spell_check('x');
		}

		if(typed.equals("Y")) {
			y.setEnabled(false);
			spell_check('y');
		}

		if(typed.equals("Z")) {
			z.setEnabled(false);
			spell_check('z');
		}
	}
	class WindowEventHandler extends WindowAdapter {
		public void windowClosing(WindowEvent e) {
                	dispose();
		}
	}
}


