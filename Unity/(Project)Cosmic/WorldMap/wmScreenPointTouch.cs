using UnityEngine;
using System.Collections;
using UnityEngine.UI;
public class wmScreenPointTouch : MonoBehaviour
{
    string zodiac;
    void Update()
    {
        if (WorldMapManager.Instance().dragState == false)
        {
            //if (Input.GetButtonUp("Fire1"))                                     // Debug Mode
            //{
            //    Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);    // Debug Mode
            //    RaycastHit hit;                                                 // Debug Mode

            foreach (Touch touch in Input.touches)                        // Build Mode
            {
                Ray ray = Camera.main.ScreenPointToRay(touch.position);   // Build Mode
                RaycastHit hit;                                           // Build Mode

                if (Physics.Raycast(ray, out hit))
                {
                    if (WorldMapManager.Instance().dragState == false)
                    {
                        if (hit.transform.tag.Equals("Stars"))
                        {
                            SoundManager.Instance().PlaySfx(SoundManager.Instance().getFood);
                            SelectDB.Instance().column = "locationX,locationY,locationZ,name,zodiac";
                            SelectDB.Instance().table = "zodiacTable";
                            SelectDB.Instance().where = "WHERE zID= " + "'" + hit.transform.name + "'";
                            SelectDB.Instance().Select(1);
                            GameData.Instance().starPosition = SelectDB.Instance().starPosition;

                            WorldMapManager.Instance().ChooseStar.SetActive(false);
                            WorldMapManager.Instance().Touch.SetActive(false);
                            WorldMapManager.Instance().Destination_ui.SetActive(true);
                            
                            if (SelectDB.Instance().zodiacName == "Aquarius")
                                zodiac = "물병자리";
                            else if (SelectDB.Instance().zodiacName == "Pisces")
                                zodiac = "물고기자리";
                            else if (SelectDB.Instance().zodiacName == "Aries")
                                zodiac = "양자리";
                            else if (SelectDB.Instance().zodiacName == "Taurus")
                                zodiac = "황소자리";
                            else if (SelectDB.Instance().zodiacName == "Gemini")
                                zodiac = "쌍둥이자리";
                            else if (SelectDB.Instance().zodiacName == "Cancer")
                                zodiac = "게자리";
                            else if (SelectDB.Instance().zodiacName == "Leo")
                                zodiac = "사자자리";
                            else if (SelectDB.Instance().zodiacName == "Virgo")
                                zodiac = "처녀자리";
                            else if (SelectDB.Instance().zodiacName == "Libra")
                                zodiac = "천칭자리";
                            else if (SelectDB.Instance().zodiacName == "Scorpius")
                                zodiac = "전갈자리";
                            else if (SelectDB.Instance().zodiacName == "Sagittarius")
                                zodiac = "궁수자리";
                            else if (SelectDB.Instance().zodiacName == "Capricornus")
                                zodiac = "염소자리";

                            WorldMapManager.Instance().Destination_ui.GetComponentInChildren<Text>().text = zodiac + " "+ SelectDB.Instance().starName;
                        }
                        //else
                        //{
                        //    WorldMapManager.Instance().Touch.SetActive(false);
                        //    WorldMapManager.Instance().Destination_ui.SetActive(true);
                        //    WorldMapManager.Instance().Destination_ui.GetComponentInChildren<Text>().text = hit.transform.name;
                        //}
                    }
                }
                }                                                             // Build Mode
            //}                                                                   // Debug Mode
        }
        WorldMapManager.Instance().dragState = false;
    }
}
