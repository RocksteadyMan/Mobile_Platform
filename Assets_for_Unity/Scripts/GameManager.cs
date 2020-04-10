using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using UnityEngine.UI;
using UnityEngine.EventSystems;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    [SerializeField]
    private Text log;
    public GameObject menuPanel;
    public static GameObject sMenu;
    public Image image;
    public Vector2 force;
    public byte[] m;//массив байтов
    public Text recconect;
    public Button buttonrecconect;

    public bool isButton;
    public int yfl = 0, xfl = 0;

    public int yF, xF;
    public int r,l;
    public InputField inputField1, inputField2, inputField3;
    public float iF1 = -1, iF2 = -1, iF3 = -1;
    public string inc1, inc1_pre, inc1_post;

    public float time = 0;
    public string pre, post1, post2;
    public byte preB, post1B, post2B;
    public GameObject panelInputs;
    public Sprite red, green;
    public byte[] aB;
    
    public bool isCoofMessagening = false;
    private bool isGet;
    public Text messageGet;
    public Vector2 forceOld;

    public void ShowPanelInputs()
    {
        panelInputs.SetActive(true);
    }
    public void HidePanelInputs()
    {
        panelInputs.SetActive(false);
    }
    public void MessageCoof()
    {
        aB = new byte[9];
        try
        {
            int ck = 0;
            float f1, f2, f3;
            f1 = Convert.ToSingle(inputField1.text);
            f2 = Convert.ToSingle(inputField2.text);
            f3 = Convert.ToSingle(inputField3.text);
            string[] s;
            if (((int)f1) == f1)
            {
                aB[0] = (byte)f1;
                aB[1] = 0;
                aB[2] = 0;
            }
            else
            {
                 s = inputField1.text.Split('.');

                pre = s[0];
                post1 = s[1][0].ToString() + s[1][1].ToString();
                post2 = s[1][2].ToString() + s[1][3].ToString();
                preB = Convert.ToByte(pre);
                post1B = Convert.ToByte(post1);
                post2B = Convert.ToByte(post2);
                aB[0] = preB;
                aB[1] = post1B;
                aB[2] = post2B;
            }
            if (((int)f2) == f2)
            {
                aB[3] = (byte)f2;
                aB[4] = 0;
                aB[5] = 0;
            }
            else
            {
                s = inputField2.text.Split('.');

                pre = s[0];
                post1 = s[1][0].ToString() + s[1][1].ToString();
                post2 = s[1][2].ToString() + s[1][3].ToString();
                preB = Convert.ToByte(pre);
                post1B = Convert.ToByte(post1);
                post2B = Convert.ToByte(post2);
                aB[3] = preB;
                aB[4] = post1B;
                aB[5] = post2B;
            }
            if (((int)f3) == f3)
            {
                aB[6] = (byte)f3;
                aB[7] = 0;
                aB[8] = 0;
            }
            else
            {
                s = inputField3.text.Split('.');

                pre = s[0];
                post1 = s[1][0].ToString() + s[1][1].ToString();
                post2 = s[1][2].ToString() + s[1][3].ToString();
                preB = Convert.ToByte(pre);
                post1B = Convert.ToByte(post1);
                post2B = Convert.ToByte(post2);
                aB[6] = preB;
                aB[7] = post1B;
                aB[8] = post2B;
            }
            TestPlugin.SetMessage(aB);//отправка 
        }
        catch (Exception e)
        {
            Debug.LogError(e.Message + " " + e.StackTrace);
        }
    }
    public void GET()
    {
        aB = new byte[] { (byte)'G', (byte)'E', (byte)'T' };
        TestPlugin.SetMessage(aB);
        isGet = false;
    }
    public void SET()
    {
        aB = new byte[] { (byte)'S', (byte)'E', (byte)'T' };
        TestPlugin.SetMessage(aB);
        isGet = true;
    }
    double convert(double value, double From1, double From2, double To1, double To2)
    {
        return (value - From1) / (From2 - From1) * (To2 - To1) + To1;
    }
    public void VerticalJoyStic()
    {
        yF = Mathf.Abs((int)force.y);//считываем с вертикального джойстика и делаем модуль полученного числа
        xF = Mathf.Abs((int)force.x);//считываем с горизонтального джойстика и делаем модуль полученного числа
        if (force.x > 0 & force.y != 0)//если горизонт больше 0, т.е. вправо, и верткаль не равна нулю, т.е. едем вперёд/назад
        {
            xF = (int)convert(xF, 0, 255, yF, 0);
            xF = (int)(xF * 0.25f);
            yF = (int)(yF * 0.25f);//вертикаль присваиваем переменной
            for (int i = 0; i < 6; i++)//задаём мощь движкам
            {

                if (TestPlugin.checkbit((byte)xF, i) == 1)
                {
                    m[0] = TestPlugin.setbit(m[0], i);
                }
                else
                {
                    m[0] = TestPlugin.unsetbit(m[0], i);
                }
                if (TestPlugin.checkbit((byte)yF, i) == 1)
                {
                    m[1] = TestPlugin.setbit(m[1], i);
                }
                else
                {
                    m[1] = TestPlugin.unsetbit(m[1], i);
                }

            }
            //задаём ориентацию движкам
            if (force.y > 0)
            {
                m[0] = TestPlugin.setbit(m[0], 6);
                m[1] = TestPlugin.setbit(m[1], 6);
            }
            else
            {
                m[0] = TestPlugin.unsetbit(m[0], 6);
                m[1] = TestPlugin.unsetbit(m[1], 6);
            }
        }
        else if (force.x < 0 & force.y != 0)//аналогично вышестоящему коду, только наоборот
        {
            xF = (int)convert(xF, 0, 255, yF, 0);
            xF = (int)(xF * 0.25f);
            yF = (int)(yF * 0.25f);//вертикаль присваиваем переменной
            for (int i = 0; i < 6; i++)//задаём мощь движкам
            {

                if (TestPlugin.checkbit((byte)yF, i) == 1)
                {
                    m[0] = TestPlugin.setbit(m[0], i);
                }
                else
                {
                    m[0] = TestPlugin.unsetbit(m[0], i);
                }
                if (TestPlugin.checkbit((byte)xF, i) == 1)
                {
                    m[1] = TestPlugin.setbit(m[1], i);
                }
                else
                {
                    m[1] = TestPlugin.unsetbit(m[1], i);
                }

            }
            //задаём ориентацию движкам
            if (force.y > 0)
            {
                m[0] = TestPlugin.setbit(m[0], 6);
                m[1] = TestPlugin.setbit(m[1], 6);
            }
            else
            {
                m[0] = TestPlugin.unsetbit(m[0], 6);
                m[1] = TestPlugin.unsetbit(m[1], 6);
            }
        }
        else if (force.x > 0 & force.y == 0)//если только горизонт, вправо
        {
            r = xF;//присваиваем горизонт переменной
            r = (int)(r * 0.25f);//делим на 4
            for (int i = 0; i < 6; i++)//так же мощность движкам задаём
            {
                if (TestPlugin.checkbit((byte)r, i) == 1)
                {
                    m[0] = TestPlugin.setbit(m[0], i);
                    m[1] = TestPlugin.setbit(m[1], i);
                }
                else
                {
                    m[0] = TestPlugin.unsetbit(m[0], i);
                    m[1] = TestPlugin.unsetbit(m[1], i);
                }
            }

            m[0] = TestPlugin.unsetbit(m[0], 6);//на всякий очищаем биты, и ставим на левый, направление назад
            m[1] = TestPlugin.unsetbit(m[1], 6);
            m[1] = TestPlugin.setbit(m[1], 6);//устанавливаем, на правый мотор направление вперёд
        }
        else if (force.x < 0 & force.y == 0)//аналогично тому, что выше, только наоборот
        {
            l = xF;
            l = (int)(l * 0.25f);
            for (int i = 0; i < 6; i++)
            {
                if (TestPlugin.checkbit((byte)l, i) == 1)
                {
                    m[0] = TestPlugin.setbit(m[0], i);
                    m[1] = TestPlugin.setbit(m[1], i);
                }
                else
                {
                    m[0] = TestPlugin.unsetbit(m[0], i);
                    m[1] = TestPlugin.unsetbit(m[1], i);
                }
            }

            m[0] = TestPlugin.unsetbit(m[0], 6);
            m[1] = TestPlugin.unsetbit(m[1], 6);
            m[0] = TestPlugin.setbit(m[0], 6);
        }
        else//если только вертикаль
        {
            yF = (int)(yF * 0.25f);//вертикаль присваиваем переменной
            for (int i = 0; i < 6; i++)//задаём мощь движкам
            {

                if (TestPlugin.checkbit((byte)yF, i) == 1)
                {
                    m[0] = TestPlugin.setbit(m[0], i);
                    m[1] = TestPlugin.setbit(m[1], i);
                }
                else
                {
                    m[0] = TestPlugin.unsetbit(m[0], i);
                    m[1] = TestPlugin.unsetbit(m[1], i);
                }
            }
            //задаём ориентацию движкам
            if (force.y > 0)
            {
                m[0] = TestPlugin.setbit(m[0], 6);
                m[1] = TestPlugin.setbit(m[1], 6);
            }
            else
            {
                m[0] = TestPlugin.unsetbit(m[0], 6);
                m[1] = TestPlugin.unsetbit(m[1], 6);
            }
        }
        TestPlugin.SetMessage(m);
    }
    public void CalcJoystic()//расчёт байтов
    {
        yF = Mathf.Abs((int)force.y);//считываем с вертикального джойстика и делаем модуль полученного числа


        xF = Mathf.Abs((int)force.x);//считываем с горизонтального джойстика и делаем модуль полученного числа

        if (yF > 0)//если больше нуля, то проводим следующие операции
        {
            yF += 31;//прибавляем 31(до минимума чтобы догнать по мощи) 
            yF = Mathf.Clamp(yF, 31, 255);//смотрим, чтобы не вышло за пределы, в противном случае, ставим один из пределов в качестве значения, если меньше 31, то ставим 31, если больше 255, ставим 255
        }
        if (xF > 0)//так же как и сверху, только для горизонта
        {
            xF += 31;
            xF = Mathf.Clamp(xF, 31, 255);
        }

        if (force.x > 0 & force.y != 0)//если горизонт больше 0, т.е. вправо, и верткаль не равна нулю, т.е. едем вперёд/назад
        {
            r = (int)(xF * 0.5f);//т.к. у нас это поворот, то умножаем на половину, дабы скорость поворота правого движка, была в два раза меньше левого, для поворота.
            r = (int)(r * 0.25f);//умножаем так же оба движка на 1/4, для того, чтобы вместилось значение в 6 бит(тут правый)
            yF = (int)(yF * 0.25f);//левый
            for (int i = 0; i < 6; i++)//в цикле проходимся по битам из переменных выше и заносим их в массив байтов (мощность движков)
            {
                if (TestPlugin.checkbit((byte)r, i) == 1)
                {
                    m[0] = TestPlugin.setbit(m[0], i);

                }
                else
                {
                    m[0] = TestPlugin.unsetbit(m[0], i);
                }
                if (TestPlugin.checkbit((byte)(yF), i) == 1)
                {
                    m[1] = TestPlugin.setbit(m[1], i);
                }
                else
                {
                    m[1] = TestPlugin.unsetbit(m[1], i);
                }
            }
            if (force.y > 0)//направление, если вперёд, то устанавливаем биты, иначе снимаем
            {
                m[0] = TestPlugin.setbit(m[0], 6);
                m[1] = TestPlugin.setbit(m[1], 6);
            }
            else
            {
                m[0] = TestPlugin.unsetbit(m[0], 6);
                m[1] = TestPlugin.unsetbit(m[1], 6);
            }
        }
        else if (force.x < 0 & force.y != 0)//аналогично вышестоящему коду, только наоборот
        {
            l = (int)(xF * 0.5f);
            l = (int)(l * 0.25f);
            yF = (int)(yF * 0.25f);
            for (int i = 0; i < 6; i++)
            {
                if (TestPlugin.checkbit((byte)yF, i) == 1)
                {
                    m[0] = TestPlugin.setbit(m[0], i);

                }
                else
                {
                    m[0] = TestPlugin.unsetbit(m[0], i);
                }
                if (TestPlugin.checkbit((byte)(l), i) == 1)
                {
                    m[1] = TestPlugin.setbit(m[1], i);
                }
                else
                {
                    m[1] = TestPlugin.unsetbit(m[1], i);
                }
            }
            if (force.y > 0)
            {

                m[0] = TestPlugin.setbit(m[0], 6);
                m[1] = TestPlugin.setbit(m[1], 6);
            }
            else
            {
                m[0] = TestPlugin.unsetbit(m[0], 6);
                m[1] = TestPlugin.unsetbit(m[1], 6);
            }
        }
        else if (force.x > 0 & force.y == 0)//если только горизонт, вправо
        {
            r = xF;//присваиваем горизонт переменной
            r = (int)(r * 0.25f);//делим на 4
            for (int i = 0; i < 6; i++)//так же мощность движкам задаём
            {
                if (TestPlugin.checkbit((byte)r, i) == 1)
                {
                    m[0] = TestPlugin.setbit(m[0], i);
                    m[1] = TestPlugin.setbit(m[1], i);
                }
                else
                {
                    m[0] = TestPlugin.unsetbit(m[0], i);
                    m[1] = TestPlugin.unsetbit(m[1], i);
                }
            }

            m[0] = TestPlugin.unsetbit(m[0], 6);//на всякий очищаем биты, и ставим на левый, направление назад
            m[1] = TestPlugin.unsetbit(m[1], 6);
            m[1] = TestPlugin.setbit(m[1], 6);//устанавливаем, на правый мотор направление вперёд
        }
        else if (force.x < 0 & force.y == 0)//аналогично тому, что выше, только наоборот
        {
            l = xF;
            l = (int)(l * 0.25f);
            for (int i = 0; i < 6; i++)
            {
                if (TestPlugin.checkbit((byte)l, i) == 1)
                {
                    m[0] = TestPlugin.setbit(m[0], i);
                    m[1] = TestPlugin.setbit(m[1], i);
                }
                else
                {
                    m[0] = TestPlugin.unsetbit(m[0], i);
                    m[1] = TestPlugin.unsetbit(m[1], i);
                }
            }

            m[0] = TestPlugin.unsetbit(m[0], 6);
            m[1] = TestPlugin.unsetbit(m[1], 6);
            m[0] = TestPlugin.setbit(m[0], 6);
        }
        else//если только вертикаль
        {
            yF = (int)(yF * 0.25f);//вертикаль присваиваем переменной
            for (int i = 0; i < 6; i++)//задаём мощь движкам
            {

                if (TestPlugin.checkbit((byte)yF, i) == 1)
                {
                    m[0] = TestPlugin.setbit(m[0], i);
                    m[1] = TestPlugin.setbit(m[1], i);
                }
                else
                {
                    m[0] = TestPlugin.unsetbit(m[0], i);
                    m[1] = TestPlugin.unsetbit(m[1], i);
                }
            }
            //задаём ориентацию движкам
            if (force.y > 0)
            {
                m[0] = TestPlugin.setbit(m[0], 6);
                m[1] = TestPlugin.setbit(m[1], 6);
            }
            else
            {
                m[0] = TestPlugin.unsetbit(m[0], 6);
                m[1] = TestPlugin.unsetbit(m[1], 6);
            }
        }
        
        TestPlugin.SetMessage(m);//отправка 
        Debug.Log("Произошла отправка");
        
        
    }
    public void ExitListDevices()//выходим из списка устройств 
    {
        menuPanel.SetActive(false);
    }
    void Update()
    {
        try
        {
            //if (force != forceOld)
            //{
               // forceOld = force;
                VerticalJoyStic();
            //string gM = TestPlugin.GetMessage();
            // if (gM != "-2" & gM != "-1")
            //    messageGet.text = gM;
            //}
            messageGet.text = TestPlugin.GetMessage();
            TestPlugin.GetStatus(image, red, green);//получаем статус подключения устройства
        }
        catch (Exception e)
        {
            Debug.LogError(e.Message);
        }
    }
    void Awake()//стартовый метод, запускается самым первым при старте сцены
    {
        m = new byte[2];//инициализируем массив байтов
        TestPlugin.Init();//инициализируем джава класс
        sMenu = menuPanel;//инициализируем панель меню

        TestPlugin.GetStatus(image,red,green);//получаем статус подключения устройства

    }
    public void LVLLoad()//загрузка уровня с моделью платформы
    {
        SceneManager.LoadScene("model");
    }
    public void Recconnect()//производим переподключение
    {
        TestPlugin.Recconnect();
    }
    public void ShowDevaces()//показываем устройства которые обнаружил блютуз
    {
        TestPlugin.ShowDevaces();
    }
    public void Exit()//выходим из приложения
    {
        Application.Quit();
    }
    public void Kek()
    {
        TestPlugin.Kek(log);
    }
    public void Show()//показываем 
    {
        TestPlugin.Show();
    }
    public void Right()//пустота
    {
           
    }
    public void Left()//так же
    {
        
    }
    public void Jump()//соленоид вкл
    {
        //задаём на 7 позиции биты
        m[1] = TestPlugin.unsetbit(m[1], 7);
        m[0] = TestPlugin.unsetbit(m[0], 7);
        m[1] = TestPlugin.setbit(m[1], 7);
        m[0] = TestPlugin.setbit(m[0], 7);
        TestPlugin.SetMessage(m);
        Debug.Log("Произошла отправка");
    }
    public void UnJump()//соленоид выкл 
    {
        //убираем биты с 7 позиции
        m[1] = TestPlugin.unsetbit(m[1], 7);
        m[0] = TestPlugin.unsetbit(m[0], 7);
        TestPlugin.SetMessage(m);
        Debug.Log("Произошла отправка");
    }
    public void ShowDeviceName()
    {
        TestPlugin.ShowDeviceName(log);
    }
    public void OpenMenu()//открытие меню
    {
        menuPanel.SetActive(true);
    }
    public void CloseMenu()//закрытие меню
    {
        menuPanel.SetActive(false);
    }
    public void GetMessage()
    {
        log.text = TestPlugin.GetMessage();
    }
    public class TestPlugin//класс для работы с джава плагином
    {
        private const string NAME_CLASS = "com.example.bluetoothplugin.BluetoothPlugin";
        private static AndroidJavaClass jC;
        public static void Init()//инициализация
        {
            jC = new AndroidJavaClass(NAME_CLASS);
            jC.CallStatic("Init");
        }
        public static void Show()//показываем поиск устройств
        {

            if (jC != null)
            {
                jC.CallStatic("searchDevices");
            }
        }
        public static void ShowDevaces()//показываем все девайсы
        {
            jC.CallStatic("showListDevices");
        }
        public static string GetMessage()//поулчаем месседж
        {
            return jC.CallStatic<int>("getMessage").ToString();
        }
        public static void ShowDeviceName(Text log)//получаем имя устройства
        {
            log.text = jC.CallStatic<string>("getNameDevice", 0);
        }
        public static void Kek(Text log)
        {
            log.text = jC.CallStatic<int>("ReturnCountDevices").ToString();
        }
        static public byte checkbit(byte value, int position)//чекаем бит
        {
            byte result;
            if ((value & (1 << position)) == 0)
            {
                result = 0;
            }
            else
            {
                result = 1;
            }
            return result;
        }

        static public byte setbit(byte value, int position)//устанавливаем бит в 1
        {
            return (byte)(value | (1 << position));
        }

        static public byte unsetbit(byte value, int position)//устанавливаем бит в 0
        {
            return (byte)(value & ~(1 << position));
        }
        public static void SetMessage(byte[] m)//отправляем 
        {

            jC.CallStatic("setMessage", m);
        }

        public static void Recconnect()//переподключение
        {
            jC.CallStatic("Recconnect");
        }
        internal static void GetStatus(Image image, Sprite red, Sprite green)//статус устройства
        {
            if (jC == null) return;
            try
            {
                Debug.Log("void GetStatus unity START");
                if (jC.CallStatic<string>("GetStatus") == "Подключение прошло успешно!")
                {
                    Debug.Log("void GetStatus unity GREEN STATUS");
                    image.sprite = green;
                    //image.color = Color.green;
                    //string mac = jC.CallStatic<string>("GetMac");
                    //PlayerPrefs.SetString("Mac", mac);
                    //PlayerPrefs.Save();
                }
                else
                {
                    Debug.Log("void GetStatus unity RED STATUS");
                    image.sprite = red;
                    //image.color = Color.red;
                }
                Debug.Log("void GetStatus unity END");
            }
            catch (Exception e)
            {

                Debug.LogError(e.Message);
                Debug.LogError("void GetStatus unity HDE TO");
            }
            
        }
    }
}
