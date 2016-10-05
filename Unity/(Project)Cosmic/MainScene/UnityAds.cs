using UnityEngine;
using System.Collections;
using UnityEngine.UI;
#if UNITY_ADS
using UnityEngine.Advertisements;
#endif


public class UnityAds : MonoBehaviour {



    public void ShowRewardedAd()
    {
        if (Advertisement.IsReady())
        {
            ShowOptions options = new ShowOptions();
            options.resultCallback = HandleShowResult;
            Advertisement.Show(null, options);
        }
    }



    private void HandleShowResult(ShowResult result)
    {
        switch (result)
        {
            case ShowResult.Finished:
                Debug.Log("The ad was successfully shown.");

                MainSingleTon.Instance.cPE += 20;
                string Query1 = "UPDATE userTable SET cPE = " + MainSingleTon.Instance.cPE;

                GameObject.Find("GameManager/SqlManager").GetComponent<MainSceneSQL>().UpdateQuery(Query1);

                break;
            case ShowResult.Skipped:
                Debug.Log("The ad was skipped before reaching the end.");
                break;
            case ShowResult.Failed:
                Debug.LogError("The ad failed to be shown.");
                break;
        }
    }


}
