import java.io.*;
import java.util.*;


public class HashMapTest {
	public static void main(String[] args) throws IOException
	{
		//map <Ű, ���> -> Ű�� �ߺ��� ������� ����
		// Ű�� �ߺ��� ��� ���� ����
		Map<String, String> map = new HashMap<String, String>();
		map.put ("��ȭ", "�����޺� ŰŰ");
		map.put("ȣ��", "��ũ��");
		map.put("��ȭ", "Ȳȥ���� ��������");

		System.out.println(map);
		System.out.println();

		String key;
		Set set = map.keySet();
		Iterator it = set.iterator();
		while(it.hasNext()){
			key = (String)it.next();
			System.out.println(map.get(key));
		}
		System.out.println();

		map.put("��ȭ", "����......."); //������ Ű�� ���� �����Ѵ�.
		System.out.println(map);
		System.out.println();
	}
}
