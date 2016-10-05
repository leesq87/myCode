using UnityEngine;
using System.Collections;
using UnityEngine.SceneManagement;
public class SoundManager : MonoBehaviour
{
    static SoundManager _instance = null;
    static bool bgmBegin = false;
    public static SoundManager Instance()
    {
        return _instance;
    }
    public int bgmType = 0; // 0: Default, 1 : Main, 2 : Explore 3: Change

    public AudioClip mainBGM = null;
    public AudioClip exploreBGM = null;
    public AudioClip exploreFlying1 = null;
    public AudioClip exploreFlying2 = null;
    public AudioClip uiTouch = null;
    public AudioClip SceneTran = null;
    public AudioClip planetTouch = null;
    public AudioClip dragPlanet = null;
    public AudioClip getFood = null;
    public AudioClip buyTi = null;
    public AudioClip buyFood = null;
    public AudioClip changePlanet = null;
    public AudioClip usePe = null;
    public AudioClip activeStar = null;
    public AudioClip activeSign = null;
    public AudioClip startExplore = null;
    public AudioClip endExplore = null;
    public AudioClip shipHumming = null;
    public AudioClip destroyPlanet = null;

    public AudioSource bgm;
    public AudioSource fx;
    public AudioSource ship;

    public string nextSceneName;

    void Awake()
    {
        if (_instance == null)
            _instance = this;

        if (!bgmBegin)
        {
            gameObject.name = "SoundManager_Active";
            DontDestroyOnLoad(gameObject);
            bgmBegin = true;

            if (gameObject.scene.name != "Explore")
            {
                bgm.clip = mainBGM;
                bgm.loop = true;
                bgm.Play();
            }
            else
            {
                bgm.clip = exploreBGM;
                bgm.loop = true;
                bgm.Play();
            }
        }

        if (GameObject.Find("SoundManager_Active") != null && GameObject.Find("SoundManager") != null)
        {
            Destroy(GameObject.Find("SoundManager").gameObject);
        }
    }
    void Update()
    {
        if (bgmType != 0)
        {
            if (bgm.volume != 0 && bgmType != 3)
            {
                bgm.volume -= 0.5f * Time.deltaTime;
            }
            else if (bgm.volume == 0 && bgmType != 3)
            {
                bgmChange();
                bgmType = 3;
            }
            else if (bgmType == 3)
            {
                bgm.volume += 0.5f * Time.deltaTime;
                if (bgm.volume == 1.0f)
                {
                    bgmType = 0;
                }
            }
        }
        if (bgm.clip.name == "BGM_Explore" && ship.isPlaying == false)
        {
            ship.clip = shipHumming;
            ship.loop = true;
            ship.Play();
        }else if(bgm.clip.name != "BGM_Explore" && ship.isPlaying == true)
        {
            ship.Stop();
        }

        if (bgm.clip.name == "BGM_Explore" && fx.isPlaying == false)
        {
            int fxRand = Random.Range(1, 2);
            if(fxRand == 1)
            {
                PlaySfx(exploreFlying1);
            }else if (fxRand == 2)
            {
                PlaySfx(exploreFlying2);
            }
        }
        
        
    }
    public void PlaySfx(AudioClip clip)
    {
        fx.PlayOneShot(clip);
    }

    public void bgmChange()
    {
        if (bgmType == 1)
        {
            bgm.clip = mainBGM;
            bgm.loop = true;
            bgm.Play();
        }
        else if (bgmType == 2)
        {
            bgm.clip = exploreBGM;
            bgm.loop = true;
            bgm.Play();
        }
    }

}