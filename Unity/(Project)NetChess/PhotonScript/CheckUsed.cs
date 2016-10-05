using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class CheckUsed : MonoBehaviour {

    public List<roomState> RList = new List<roomState>();

    static int index;
    static int count = 0;

    public void Awake()
    {
        index = count;
        count++;
        if (index != 0)
            DontDestroyOnLoad(this.transform);
        else
            Destroy(this.transform);
    }
    
    //리스트에 추가
    public void getRoomList(string str)
    {
        Debug.Log("getRoomList");
        foreach (roomState RS in RList)
        {
            Debug.Log(RS.RoomName);
            if (RS.RoomName == str)
                return;
        }
        roomState newRoom = new roomState();
        newRoom.RoomName = str;
        newRoom.canUse = true;
        RList.Add(newRoom);
    }
    //리스트에서 제거
    public void deleteRoomState(string str)
    {
        foreach(roomState RS in RList)
        {
            Debug.Log(RS.RoomName);
            if (RS.RoomName == str)
            {
                RList.Remove(RS);
            }
        }
    }
    //사용자가 방을 새로 만들었을경우
    public void setRoomState(string str)
    {
        Debug.Log("setRoomstare");
        foreach(roomState RS in RList)
        {
            Debug.Log(RS.RoomName);
            if(RS.RoomName == str)
            {
                RS.canUse = true;
            }
        }
    }
    //새로운 방이 아니고, 사용했을경우
    public void setRoomUse(string str)
    {
        Debug.Log("setRoomuse");
        foreach(roomState RS in RList)
        {
            Debug.Log(RS.RoomName);
            if (RS.RoomName == str)
            {
                RS.canUse = false;
            }
        }
    }
    //방 입장전 사용여부 확인
    public bool checkUsed(string str)
    {
        foreach (roomState RS in RList)
        {
            if (RS.RoomName == str)
            {
                return RS.canUse;
            }
        }
        return true;
    }
}
public class roomState
{
    public string RoomName;
    public bool canUse;
}