#include "sortwindow2.h"
#include "ui_sortwindow2.h"
#include <ctime>
#include <QTimer>
#include <QMessageBox>
#include <menuwindow.h>
#include <QProcess>

SortWindow2::SortWindow2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SortWindow2)
{
    ui->setupUi(this);
    srand(time(NULL));

    effect->setBlurRadius(30);
    effect->setColor("#BCBEC0");
    ui->label_11->setGraphicsEffect(effect);

    effect2->setBlurRadius(30);
    effect2->setColor("#BCBEC0");
    ui->label_12->setGraphicsEffect(effect2);

    ui->pushButton_11->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid green;}"
                                     "QPushButton:hover{background: #ADD8E6; border:none; color: black;}");
    effect3->setBlurRadius(30);
    effect3->setColor("#BCBEC0");
    ui->pushButton_11->setGraphicsEffect(effect3);
    ui->pushButton_12->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid green;}"
                                     "QPushButton:hover{background: #ADD8E6; border:none; color: black;}");
    ui->pushButton_14->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid green;}"
                                     "QPushButton:hover{background: #ADD8E6; border:none; color: black;}");
    ui->pushButton_15->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid green;}"
                                     "QPushButton:hover{background: #ADD8E6; border:none; color: black;}");
    ui->pushButton_16->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid green;}"
                                     "QPushButton:hover{background: #ADD8E6; border:none; color: black;}");
    ui->pushButton_17->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid green;}"
                                     "QPushButton:hover{background: #ADD8E6; border:none; color: black;}");
    ui->pushButton_19->setStyleSheet("QPushButton{background: #F1F2F2; border: 0px solid green;}"
                                     "QPushButton:hover{background: #ADD8E6; border:none; color: black;}");

    buttonList[0] = ui->label;
    buttonList[1] = ui->label_2;
    buttonList[2] = ui->label_3;
    buttonList[3] = ui->label_4;
    buttonList[4] = ui->label_5;
    buttonList[5] = ui->label_6;
    buttonList[6] = ui->label_7;
    buttonList[7] = ui->label_8;

    for (int i = 0; i < n; i++) {
        buttonList[i]->setAlignment(Qt::AlignHCenter);

        buttonList[i]->setStyleSheet("background: #ADD8E6");

        int rnd = 2 + rand() % (20-2+1);
        buttonList[i]->setText(QString::number(rnd));

        buttonList[i]->setFixedHeight(buttonList[i]->text().toInt() * 10);
        buttonList[i]->setFixedWidth(40);
    }

    InputValues();
}

SortWindow2::~SortWindow2()
{
    delete ui;
}

void SortWindow2::on_pushButton_17_clicked()
{
    bubble = true;
    selection = false;
    insertion = false;
    shaker = false;
    ui->label_9->setText("BUBBLE SORT");
    ui->label_10->setText("Кол-во перестоновок: 0");
}

void SortWindow2::on_pushButton_14_clicked()
{
    bubble = false;
    selection = true;
    insertion = false;
    shaker = false;
    ui->label_9->setText("SELECTION SORT");
    ui->label_10->setText("Кол-во перестоновок: 0");
}

void SortWindow2::on_pushButton_16_clicked()
{
    bubble = false;
    selection = false;
    insertion = true;
    shaker= false;
    ui->label_9->setText("INSERTION SORT");
    ui->label_10->setText("Кол-во перестоновок: 0");
}

void SortWindow2::on_pushButton_15_clicked()
{
    bubble = false;
    selection = false;
    insertion = false;
    shaker = true;
    ui->label_9->setText("SHAKER SORT");
    ui->label_10->setText("Кол-во перестоновок: 0");
}

void SortWindow2::on_pushButton_11_clicked()
{
    if (bubble == true) {
        count = 0;
        ui->label_10->setText("Кол-во перестоновок: 0");
        isWork = true;
        Enabled();
        for (int i = 0; i < n-1; i++) {
            for (int j = 0; j < n-i-1; j++) {
                if (buttonList[j]->text().toInt() > buttonList[j+1]->text().toInt()) {
                    countReangements(count);
                    QLabel* temp = buttonList[j];
                    buttonList[j] = buttonList[j+1];
                    buttonList[j+1] = temp;

                    buttonList[j]->setStyleSheet("background: green");
                    buttonList[j+1]->setStyleSheet("background: green");

                    Animation(j);
                    AnimationSecondEl(j);
                    timeChange(1500);

                    buttonList[j]->setStyleSheet("background: #ADD8E6");
                    buttonList[j+1]->setStyleSheet("background: #ADD8E6");
                }
                else {
                    buttonList[j]->setStyleSheet("background: green");
                    buttonList[j+1]->setStyleSheet("background: green");

                    timeChange(1000);

                    buttonList[j]->setStyleSheet("background: #ADD8E6");
                    buttonList[j+1]->setStyleSheet("background: #ADD8E6");
                }
            }
        }
        isWork = false;
        Enabled();
    }
    else if (selection == true) {
        count = 0;
        isWork = true;
        Enabled();
        ui->label_10->setText("Кол-во перестоновок: 0");
        for (int startIndex = 0; startIndex < n - 1; ++startIndex) {
            int smallINdex = startIndex;

            buttonList[startIndex]->setStyleSheet("background: red");

            for (int currentIndex = startIndex + 1; currentIndex < n; ++currentIndex) {
                buttonList[currentIndex]->setStyleSheet("background: green");
                timeChange(500);
                buttonList[currentIndex]->setStyleSheet("background: #ADD8E6");

                if (buttonList[currentIndex]->text().toInt() < buttonList[smallINdex]->text().toInt()) {
                   if (smallINdex != startIndex)
                      buttonList[smallINdex]->setStyleSheet("background: #ADD8E6");
                   smallINdex = currentIndex;
                   buttonList[smallINdex]->setStyleSheet("background: red");
                }
            }

            QLabel* temp = buttonList[startIndex];
            buttonList[startIndex] = buttonList[smallINdex];
            buttonList[smallINdex] = temp;

            QLabel* btn = buttonList[startIndex];
            QPropertyAnimation* animation = new QPropertyAnimation(btn, "geometry");
            animation->setDuration(1000);
            animation->setEasingCurve(QEasingCurve::Linear);
            animation->setEndValue(QRectF(buttonList[smallINdex]->x() , buttonList[smallINdex]->y(), n, n));
            animation->start(QAbstractAnimation::DeleteWhenStopped);

            QLabel* btn2 = buttonList[smallINdex];
            QPropertyAnimation* animation2 = new QPropertyAnimation(btn2, "geometry");
            animation2->setDuration(1000);
            animation2->setEasingCurve(QEasingCurve::Linear);
            animation2->setEndValue(QRectF(buttonList[startIndex]->x() , buttonList[startIndex]->y(), n, n));
            animation2->start(QAbstractAnimation::DeleteWhenStopped);

            buttonList[smallINdex]->setStyleSheet("background: red");
            timeChange(1000);
            buttonList[smallINdex]->setStyleSheet("background: #ADD8E6");
            buttonList[startIndex]->setStyleSheet("background: #ADD8E6");

            if (smallINdex != startIndex) {
                countReangements(count);
            }
        }
        isWork = false;
        Enabled();
    }
    else if (insertion == true) {
        count = 0;
        ui->label_10->setText("Кол-во перестоновок: 0");
        isWork = true;
        Enabled();
        for(int i=1;i<n;i++) {
            buttonList[i]->setStyleSheet("background: red");
            timeChange(500);
            for(int j=i;j>0 && buttonList[j-1]->text().toInt()>buttonList[j]->text().toInt();j--) {// пока j>0 и элемент j-1 > j, x-массив int
                countReangements(count);

                QLabel* temp = buttonList[j-1];
                buttonList[j-1] = buttonList[j];
                buttonList[j] = temp;

                buttonList[j]->setStyleSheet("background: green");

                Animation(j);
                AnimationSecondEl(j);

                buttonList[j-1]->setStyleSheet("background: red");

                timeChange(1200);
            }
            clear();
        }
        isWork = false;
        Enabled();
    }
    else if (shaker == true) {
        count = 0;
        ui->label_10->setText("Кол-во перестоновок: 0");
        isWork = true;
        Enabled();
        int leftMark = 1;
        int rightMark = n - 1;

        while (leftMark <= rightMark)
        {
            for (int i = rightMark; i >= leftMark; i--) {
              buttonList[i]->setStyleSheet("background: blue");
              buttonList[i-1]->setStyleSheet("background: blue");

              timeChange(700);

              if (buttonList[i - 1]->text().toInt() > buttonList[i]->text().toInt()) {
                   countReangements(count);
                   QLabel* temp = buttonList[i];
                   buttonList[i] = buttonList[i-1];
                   buttonList[i-1] = temp;

                   Animation(i);
                   AnimationSecondEl(i);
                   timeChange(1200);
               }

               buttonList[i]->setStyleSheet("background: #ADD8E6");
               buttonList[i-1]->setStyleSheet("background: #ADD8E6");

            }
            leftMark++;


            for (int i = leftMark; i <= rightMark; i++) {
              buttonList[i]->setStyleSheet("background: yellow");
              buttonList[i-1]->setStyleSheet("background: yellow");

              timeChange(700);

              if (buttonList[i - 1]->text().toInt() > buttonList[i]->text().toInt()) {
                   countReangements(count);
                   QLabel* temp = buttonList[i];
                   buttonList[i] = buttonList[i-1];
                   buttonList[i-1] = temp;

                   Animation(i);
                   AnimationSecondEl(i);
                   timeChange(1200);
               }
               buttonList[i]->setStyleSheet("background: #ADD8E6");
               buttonList[i-1]->setStyleSheet("background: #ADD8E6");

            }
            rightMark--;
        }
    }
    isWork = false;
    Enabled();
}

void SortWindow2::on_pushButton_12_clicked()
{
    for (int i = 0; i < n; i++) {
        int rnd = 2 + rand() % (20-2+1);
        buttonList[i]->setText(QString::number(rnd));

        buttonList[i]->setFixedHeight(buttonList[i]->text().toInt() * 10);
        buttonList[i]->setFixedWidth(40);
    }

    InputValues();
}

void SortWindow2::on_pushButton_19_clicked()
{
    QString text = ui->lineEdit->text();
    QStringList list = text.split(",");
    for (int i = 0; i < n; i++) {
        if (list.size() == 8) {
            if (list[i].toInt() >= 2 && list[i].toInt() <= 20) {
                buttonList[i]->setText(list[i]);
                buttonList[i]->setFixedHeight(buttonList[i]->text().toInt() * 10);
                buttonList[i]->setFixedWidth(40);
            }
            else {
                QMessageBox::warning(this, tr("Ошибка"), tr("Диапозон значений должен быть [2,20]!"));//сообщение об ошибке
                break;
            }
        }
        else {
            QMessageBox::warning(this, tr("Ошибка"), tr("Количество значений должно<br> совпадать с количеством граф"));//сообщение об ошибке
            break;
        }
    }
}

void SortWindow2::timeChange(int time) {//время задержки между сменой цветов
    QEventLoop loop;
    QTimer timer;
    timer.setInterval(time); //5 sec
    connect (&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start();
    loop.exec();
}

void SortWindow2::countReangements(int& count) {
    ++count;
    QString strNum = QString::number(count);
    ui->label_10->setText("Кол-во перестоновок: " + strNum);
}

void SortWindow2::clear()
{
    for (int i = 0; i < n; i++) {
        buttonList[i]->setStyleSheet("background: #ADD8E6");
    }
}

void SortWindow2::InputValues()
{
    QString text = "";
    for (int i = 0; i < n; i++) {
        if (i != n-1)
            text += buttonList[i]->text() + ",";
        else
            text += buttonList[i]->text();
    }
    ui->lineEdit->setText(text);
}

void SortWindow2::Animation(int i) {
    QLabel* btn = buttonList[i];
    QPropertyAnimation* animation = new QPropertyAnimation(btn, "geometry");
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::Linear);
    if (bubble)
        animation->setEndValue(QRectF(buttonList[i+1]->x() , buttonList[i+1]->y(), n, n));
    else
        animation->setEndValue(QRectF(buttonList[i-1]->x() , buttonList[i-1]->y(), n, n));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

void SortWindow2::AnimationSecondEl(int i) {
    QLabel* btn2;
    if (bubble)
        btn2 = buttonList[i+1];
    else
        btn2 = buttonList[i-1];
    QPropertyAnimation* animation2 = new QPropertyAnimation(btn2, "geometry");
    animation2->setDuration(1000);
    animation2->setEasingCurve(QEasingCurve::Linear);
    animation2->setEndValue(QRectF(buttonList[i]->x() , buttonList[i]->y(), n, n));
    animation2->start(QAbstractAnimation::DeleteWhenStopped);
}


void SortWindow2::on_actionBUBBLE_triggered()
{
    QMessageBox::about(this, tr("BUBBLE SORT"), tr("<p font-style: italic><b>Сортировка пузырьком (обменная сортировка)</b>"
                                                   " – простой в реализации и малоэффективный алгоритм сортировки. "
                                                   "Метод изучается одним из первых на курсе теории алгоритмов, в то время "
                                                   "как на практике используется очень редко.</p> "
                                                   "Алгоритм состоит из повторяющихся проходов по сортируемому массиву. "
                                                   "За каждый проход элементы последовательно сравниваются попарно и, если"
                                                   "порядок в паре неверный, выполняется обмен элементов. Проходы по массиву"
                                                   "повторяются <b>N-1</b> раз или до тех пор, пока на очередном проходе не"
                                                   "окажется, что обмены больше не нужны, что означает — массив отсортирован."
                                                   "При каждом проходе алгоритма по внутреннему циклу, очередной наибольший"
                                                   "элемент массива ставится на своё место в конце массива рядом с предыдущим"
                                                   "«наибольшим элементом», а наименьший элемент перемещается на одну позицию"
                                                   "к началу массива («всплывает» до нужной позиции как пузырёк в воде, отсюда и название алгоритма)."));
}


void SortWindow2::on_actionSELECTION_triggered()
{
    QMessageBox::about(this, tr("SELECTION SORT"), tr("<p><b>Сортировка выбором</b> – возможно, самый простой в реализации алгоритм сортировки. "
                                                      "Как и в большинстве других подобных алгоритмов, в его основе лежит операция сравнения. "
                                                      "Сравнивая каждый элемент с каждым, и в случае необходимости производя обмен, метод приводит "
                                                      "последовательность к необходимому упорядоченному виду.</p>"
                                                      "<p>Идея алгоритма очень проста. Пусть имеется массив A размером N, тогда сортировка выбором"
                                                      " сводится к следующему:</p>"
                                                      "<ul><li>берем первый элемент последовательности A[i], здесь i – номер элемента, для первого i равен 1;</li>"
                                                      "<li>находим минимальный (максимальный) элемент последовательности и запоминаем его номер в переменную key;</li>"
                                                      "<li>если номер первого элемента и номер найденного элемента не совпадают, т. е. если key?1, тогда два этих элемента обмениваются значениями, иначе никаких манипуляций не происходит;</li>"
                                                      "<li>увеличиваем i на 1 и продолжаем сортировку оставшейся части массива, а именно с элемента с номером 2 по N, так как элемент A[1] уже занимает свою позицию;</li></ul>"
                                                      "<p>С каждым последующим шагом размер подмассива, с которым работает алгоритм, уменьшается на 1, но на способ сортировки это не влияет, он одинаков для каждого шага.</p>"));
}


void SortWindow2::on_actionINSERTION_triggered()
{
    QMessageBox::about(this, tr("INSERTION SORT"), tr("<p><b>Сортировка вставками</b> – простой алгоритм сортировки,"
                                                      " преимущественно использующийся в учебном программировании."
                                                      " К положительной стороне метода относится <i>простота реализации</i>,"
                                                      " а также его <i>эффективность</i> на частично упорядоченных последовательностях,"
                                                      " и/или состоящих из небольшого числа элементов. Тем не менее, высокая"
                                                      " вычислительная сложность не позволяет рекомендовать алгоритм в повсеместном использовании.</p>"
                                                      "<p>На каждом шаге алгоритма мы выбираем один из элементов входных данных"
                                                      " и вставляем его на нужную позицию в уже отсортированном списке до тех пор,"
                                                      " пока набор входных данных не будет исчерпан. Метод выбора очередного элемента"
                                                      " из исходного массива произволен; может использоваться практически любой алгоритм"
                                                      " выбора. Обычно (и с целью получения устойчивого алгоритма сортировки), элементы "
                                                      "вставляются по порядку их появления во входном массиве.</p>"));
}


void SortWindow2::on_actionMERGE_triggered()
{
    QMessageBox::about(this, tr("SHAKER SORT"), tr("<p><b>Сортировка перемешиванием, или Шейкерная сортировка, или двунаправленная </b> (англ. Cocktail sort)"
                                                   "— разновидность пузырьковой сортировки. Анализируя метод пузырьковой сортировки, можно отметить два обстоятельства.</p>"
                                                   "<p><b>Во-первых</b>, если при движении по части массива перестановки не происходят, то эта часть массива уже отсортирована"
                                                   "и, следовательно, её можно исключить из рассмотрения.</p>"
                                                   "<p><b>Во-вторых</b>, при движении от конца массива к началу минимальный элемент «всплывает» на первую позицию, а максимальный "
                                                   "элемент сдвигается только на одну позицию вправо.</p>"
                                                   "<p>Эти две идеи приводят к следующим модификациям в методе пузырьковой сортировки. Границы рабочей части массива"
                                                   "(то есть части массива, где происходит движение) устанавливаются в месте последнего обмена на каждой итерации."
                                                   "Массив просматривается поочередно справа налево и слева направо.</p>"));
}


void SortWindow2::on_action_3_triggered()
{
    QMessageBox::about(this, tr("Использование"), tr(""
                                                     "<p>1.Выберете одну из представленных сортировок.</p>"
                                                     "<p>2.Заполните графы нажав кнопку 'Случайные числа' или введите произвольные значения в текстовом поле.</p>"
                                                     "<p>3.Нажмите кнопку сортировать.</p>"));
//    QProcess process;
//    process.start("libreoffice"); //вторым парметром можно передать аргументы
    //    process.waitForFinished();
}

void SortWindow2::Enabled()
{
    if (isWork == true) {
        ui->pushButton_14->setEnabled(false);
        ui->pushButton_15->setEnabled(false);
        ui->pushButton_16->setEnabled(false);
        ui->pushButton_17->setEnabled(false);
        ui->pushButton_14->setEnabled(false);
        ui->pushButton_19->setEnabled(false);
        ui->pushButton_12->setEnabled(false);
        ui->pushButton_11->setEnabled(false);
    }
    else {
        ui->pushButton_14->setEnabled(true);
        ui->pushButton_15->setEnabled(true);
        ui->pushButton_16->setEnabled(true);
        ui->pushButton_17->setEnabled(true);
        ui->pushButton_14->setEnabled(true);
        ui->pushButton_19->setEnabled(true);
        ui->pushButton_12->setEnabled(true);
        ui->pushButton_11->setEnabled(true);
    }
}

void SortWindow2::on_action_triggered()
{

    if (isWork == true) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Дождитесь конца визуализации!"));//сообщение об ошибке
    }
    else {
        auto w = new MenuWindow();//объект главного окна
        w->setAttribute(Qt::WA_DeleteOnClose);
        w->show();//показываем окно
        deleteLater();//прячем предыдущее окно
    }
}


