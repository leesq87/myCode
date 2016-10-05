import java.applet.*;
import java.awt.event.*;
import java.awt.*;
import java.util.StringTokenizer;

import javax.swing.*;


/*<applet code="calculate" width=400 height=300></applet>*/

class ArrayStack{
	int top;
	int stackSize;
	Object itemArray[];	

	public ArrayStack(int Size) {			//스텍 생성
		top = -1;					
		stackSize = Size;			
		itemArray = new Object[stackSize];		
	}
	public boolean isEmpty() {				// 스텍이 비었는가
		return (top == -1);
	}
	public boolean isFull() {				  // 스텍이 가득 찼는가
		return (top == this.stackSize - 1);
	}
	public void push(Object item) {				// 스텍 값 입력
		itemArray[++top] = item;		
	}
	public Object pop() {					// 스텍 최상단 값 출력
		if (isEmpty()) {
			return 0;
		} else {
			return itemArray[top--];
		}
	}
	public void delete() {					// 스텍 최상단 삭제
		top--;
	}
	public Object peek() {					// 스텍 최상단 값 확인
		if (isEmpty()) {
			return 10;
		} else {
			return itemArray[top];
		}
	}
	public void printStack() {				// 스텍 결과 출력
		if (isEmpty()){
			System.out.printf("Array Stack is empty!! %n %n");
		} else {
			System.out.printf("Array Stack>> ");
			for (int i = 0; i <= top; i++)
				System.out.println(itemArray[i]);
		System.out.println();
		System.out.println();
		}
	}
}
							
class Rank{							//우선 순위 반환
	int rank(Object temp){
		if( temp.equals("(")) 		
			return 10;
		if( temp.equals("+") || temp.equals("-")) 		
			return 11;
		if( temp.equals("*") || temp.equals("/") || temp.equals("%")) 	
			return 12;
		if( temp.equals("^")) 		
			return 13;
		if( temp.equals(")"))		
			return 14;
		return -1;
	}
	int rank(String temp){
		if( temp.equals("(")) 					
			return 10;
		if( temp.equals("+") || temp.equals("-")) 		
			return 11;
		if( temp.equals("*") || temp.equals("/") || temp.equals("%")) 	
			return 12;
		if( temp.equals("^")) 						
			return 13;
		if( temp.equals(")"))						
			return 14;
		return -1;
	}
	
}


class Postfix {

	public static String fix(String e){
	
		String exp = new String("" + e);
		String fixed = new String("");


		StringTokenizer tokenizer = new StringTokenizer(exp, "+-*/()^~", true);
	
		ArrayStack stack = new ArrayStack(exp.length());

		Rank r = new Rank();
		String oper = new String("");

		
		while(tokenizer.hasMoreTokens()){				

			oper = tokenizer.nextToken();
		
			if(oper.equals("+") || oper.equals("-") || oper.equals("*") || oper.equals("/") || oper.equals("^") || oper.equals("%")){
				while(r.rank(stack.peek()) >= r.rank(oper)) 
					fixed = fixed + stack.pop() + " ";
				stack.push(oper);
			}else if(oper.equals("(")){
				stack.push(oper);
			}else if(oper.equals(")")){
				while(!stack.peek().equals("(")) 
					fixed = fixed + stack.pop() + " ";
				stack.delete();
			}else if(oper.equals("∞")){
				break;
			}else{
				fixed = fixed + oper + " ";
			}
		}

		while(stack.isEmpty() == false){
			fixed = fixed + stack.pop() + " ";
		}	
		return fixed;
		
	}
}


class Cal{
	public static String CalStr(String ex){

		String str0 = Postfix.fix(ex);		// 11*(8+2)-2^(3-2) >>> 11 8 2 + * 2 3 2 - ^ -
		ArrayStack stack0 = new ArrayStack(str0.length());

		StringTokenizer tokenizer = new StringTokenizer(str0," ");

		String oper = new String("");
	
		while(tokenizer.hasMoreTokens()){
			oper = tokenizer.nextToken();
			if ( oper.equals("~") ) {
				// 단항연산자이므로 하나만 pop시킨후 음수로 고친다.
				double a = Double.valueOf((String)stack0.pop()).doubleValue();
				a = -1 * a ;
				stack0.push(a+"");
			}
			else if(oper.equals("+") || oper.equals("-") || oper.equals("*") || oper.equals("/") || oper.equals("^") || oper.equals("%")){
				double num2 = Double.valueOf((String)stack0.pop()).doubleValue();
				double num1 = Double.valueOf((String)stack0.pop()).doubleValue();
				double temp = 0;
				if(oper.equals("+")) 
					temp = num1 + num2;
				if(oper.equals("-"))
					temp = num1 - num2;
				if(oper.equals("*"))
					temp = num1 * num2;
				if(oper.equals("/"))
					temp = num1 / num2;
				if(oper.equals("%"))
					temp = num1 % num2;
				if(oper.equals("^"))
					temp = Square(num1, num2);
				String go = Double.toString(temp);
				stack0.push(go);
			}else{
				stack0.push(oper);
			}
			oper = "";
		
		}
		return (String)stack0.pop();
	
	}

	static double Square(double x, double exp){
		double temp = 1;
		for (int i = 1; i <= exp; i++){
			temp = temp * x;
		}
		return temp;
	}
}



public class calculate extends JFrame implements ActionListener{
	String s_in = new String("");
	String s_post = new String("");
	String s_eval = new String("");

	TextField t_in = new TextField("");
	TextField t_post = new TextField("");
	TextField t_eval = new TextField("");

	Label l_main = new Label("계산기",Label.CENTER);
	Label l_in = new Label("입력:",Label.RIGHT);
	Label l_post = new Label("postfix:",Label.RIGHT);
	Label l_eval = new Label("결과:",Label.RIGHT);

	Button blank1 = new Button("");
	
	Button one = new Button("1");
	Button two = new Button("2");
	Button three = new Button("3");
	Button four = new Button("4");
	Button five = new Button("5");
	Button six = new Button("6");
	Button seven = new Button("7");
	Button eight = new Button("8");
	Button nine = new Button("9");
	Button zero = new Button("0");
	Button add = new Button("+");
	Button sub = new Button("-");
	Button multi = new Button("*");
	Button div = new Button("/");
	Button square = new Button("^");
	Button mod = new Button("%");
	Button back = new Button("←");
	Button clean = new Button("C");
	Button enter = new Button("=");
	Button brac1 = new Button("(");
	Button brac2 = new Button(")");
	Button comma = new Button(".");
	Button sign = new Button("~");
	
	GridBagLayout gblay = new GridBagLayout();
	

	public  void main(String[] args){
		calculate ca = new calculate();
	}
	public calculate(){
		
		one.addActionListener(this);
		two.addActionListener(this);
		three.addActionListener(this);
		four.addActionListener(this);
		five.addActionListener(this);
		six.addActionListener(this);
		seven.addActionListener(this);
		eight.addActionListener(this);
		nine.addActionListener(this);
		zero.addActionListener(this);
		add.addActionListener(this);
		sub.addActionListener(this);
		multi.addActionListener(this);
		div.addActionListener(this);
		square.addActionListener(this);
		mod.addActionListener(this);
		back.addActionListener(this);
		clean.addActionListener(this);
		enter.addActionListener(this);
		brac1.addActionListener(this);
		brac2.addActionListener(this);
		comma.addActionListener(this);
		t_in.addActionListener(this);
		sign.addActionListener(this);
		
		
		setLayout(gblay);
		gbinsert(l_main, 0, 0, 4, 1);
		gbinsert(l_in,0,1,1,1);
		gbinsert(t_in,1,1,3,1);
		gbinsert(l_post,0,2,1,1);
		gbinsert(t_post,1,2,3,1);
		gbinsert(l_eval,0,3,2,1);
		gbinsert(t_eval,2,3,2,1);
		gbinsert(blank1,0,4,8,1);
		gbinsert(one,0,5,1,1);
		gbinsert(two,1,5,1,1);
		gbinsert(three,2,5,1,1);
		gbinsert(add,3,5,1,1);
		gbinsert(four,0,6,1,1);
		gbinsert(five,1,6,1,1);
		gbinsert(six,2,6,1,1);
		gbinsert(sub,3,6,1,1);
		gbinsert(seven,0,7,1,1);
		gbinsert(eight,1,7,1,1);
		gbinsert(nine,2,7,1,1);
		gbinsert(multi,3,7,1,1);
		gbinsert(zero,0,8,1,1);
		gbinsert(mod,1,8,1,1);
		gbinsert(square,2,8,1,1);
		gbinsert(div,3,8,1,1);
		gbinsert(back,0,9,1,1);
		gbinsert(brac1,1,9,1,1);
		gbinsert(comma,2,9,1,1);
		gbinsert(brac2,3,9,1,1);
		gbinsert(clean,0,10,1,1);
		gbinsert(sign, 1,10,1,1);
		gbinsert(enter,2,10,2,1);
		
		blank1.setEnabled(false);
		
		addWindowListener(new WindowHandler());
		setSize(330,350);
		setVisible(true);
		
		}
	
	public void gbinsert(Component c, int x, int y, int w, int h){
		GridBagConstraints gb = new GridBagConstraints();
		gb.fill = GridBagConstraints.HORIZONTAL;
		gb.gridx= x;
		gb.gridy = y;
		gb.gridwidth = w;
		gb.gridheight = h;
		gb.weightx = 1;
		gb.weighty = 0;
		
		gblay.setConstraints(c,gb);
		this.add(c);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String typed = e.getActionCommand();
		repaint();
		if(typed.equals("1")){
			s_in = t_in.getText() + "1";
			repaint();
		}
		if(typed.equals("2")){
			s_in = t_in.getText() + "2";
			repaint();
		}
		if(typed.equals("3")){
			s_in = t_in.getText() + "3";
			repaint();
		}
		if(typed.equals("4")){
			s_in = t_in.getText() + "4";
			repaint();
		}
		if(typed.equals("5")){
			s_in = t_in.getText() + "5";
			repaint();
		}
		if(typed.equals("6")){
			s_in = t_in.getText() + "6";
			repaint();
		}
		if(typed.equals("7")){
			s_in = t_in.getText() + "7";
			repaint();
		}
		if(typed.equals("8")){
			s_in = t_in.getText() + "8";
			repaint();
		}
		if(typed.equals("9")){
			s_in = t_in.getText() + "9";
			repaint();
		}
		if(typed.equals("0")){
			s_in = t_in.getText() + "0";
			repaint();
		}
		if(typed.equals("←")){
			if(!s_in.equals("")){ 
				String temp = s_in;
				String Backed = temp.substring(0 , temp.length() - 1);
				s_in =Backed;
				repaint();
			}
		}
		if(typed.equals("C")){
			s_in = "";
			s_post = "";
			s_eval = "";
			repaint();
		}
		if(typed.equals("+")){
			s_in = t_in.getText() + "+";
			repaint();
		}
		if(typed.equals("-")){
			s_in = t_in.getText() + "-";
			repaint();
		}
		if(typed.equals("*")){
			s_in = t_in.getText() + "*";
			repaint();
		}
		if(typed.equals("/")){
			s_in = t_in.getText() + "/";
			repaint();
		}
		if(typed.equals("(")){
			s_in = t_in.getText() + "(";
			repaint();
		}
		if(typed.equals(")")){
			s_in = t_in.getText() + ")";
			repaint();
		}
		if(typed.equals("^")){
			s_in = t_in.getText() + "^";
			repaint();
		}
		if(typed.equals("~")){
			String imsi = t_in.getText();
			if(imsi.length() !=0){
				String isOver = imsi.substring(imsi.length()-1, imsi.length());
				if(isOver.equals("~"))
					s_in = imsi.substring(0,imsi.length()-1);
				else
					s_in = t_in.getText() +"~";
			}
			else
				s_in = t_in.getText() +"~";
			repaint();
		}
		if(typed.equals("=")){
			s_in = t_in.getText();
			s_post = Postfix.fix(s_in);
			s_eval = Cal.CalStr(s_in);
			repaint();
		}
	}
	
	public void paint(Graphics g){
		t_in.setText(s_in);
		t_post.setText(s_post);
		t_eval.setText(s_eval);
	}

	public class WindowHandler extends WindowAdapter{
		public void windowClosing(WindowEvent e){
			dispose();
		}
	}
}
