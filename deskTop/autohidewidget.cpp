#include "autohidewidget.h"
#include "ui_autohidewidget.h"

autoHideWidget::autoHideWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::autoHideWidget)
{ 
    ui->setupUi(this);
    m_path.load();//当运行进程时，加载路径，即解析xml文件路径数据存储在m_choosed_path容器中，以及赋值m_count;
    reLoad();//即重新加载文件图标和按钮进窗口；
    setAcceptDrops(true);
    m_dragging = false;//判断是否有拖动程序窗口；
    is_hiding = false;//判断程序窗口是否隐藏；
    //不显示标题栏和边框
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    //设置背景（全透明）
    setAttribute(Qt::WA_TranslucentBackground);
    QPixmap close = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);//样式表标准样式；
    ui->btnClose->setIcon(close);//设置按钮图标和大小；
    ui->btnClose->setGeometry(this->geometry().x()+ this->geometry().width()-25, this->geometry().y(), 25, 25);
    m_back.load("F:/QTDemo/deskTopSoft/deskTop/image/123.png");//背景； 
    connect(ui->btnClose, SIGNAL(clicked()), this, SLOT(close_buttton_clicked()));
}

void autoHideWidget::paintEvent(QPaintEvent *evevt)
{
    QPainter painter(this);
    QRect frameRect = rect();
    painter.drawPixmap(frameRect, m_back);
}

void autoHideWidget::enterEvent(QEvent *event)
{

    int screenwidth = QApplication::desktop()->width();//鼠标进入程序窗口时，获取桌面长宽；
    int screenhight = QApplication::desktop()->height();
    if (is_hiding)
    {
        QRect erect = QRect(this->pos(), this->size());//获取当前程序窗口位置坐标；
        QPropertyAnimation*animation = new QPropertyAnimation(this, "geometry");//设置窗口动画效果；
        animation->setDuration(500);//动画效果时间；
        animation->setStartValue(erect);//动画初始位置；
        QRect enrect;//下面是计算动画end位置值并赋给enrect，我用的方法计较简单，见笑啦。。；
        if (erect.right()>screenwidth/*||(erect.right()>screenwidth&&erect.top()<0)*/)
        {
            enrect = QRect((screenwidth - this->width())+2, this->y(), this->size().width(), this->rect().height());

        }
        if (erect.left()<0 /*|| (erect.left()<0 && erect.top()<0)*/)
        {
            enrect = QRect(-1, this->y(), this->size().width(), this->rect().height());
        }
        if (erect.top()<0&&erect.left()>0&&erect.right()<screenwidth)
        {
            enrect = QRect(this->x(), -1, this->size().width(), this->rect().height());
        }
        animation->setEndValue(enrect);//设置动画end值；
        animation->start();
        is_hiding = false;//解除隐藏状态；
    }
}

void autoHideWidget::leaveEvent(QEvent *event)
{

    int screenwidth = QApplication::desktop()->width();
    int screenhight = QApplication::desktop()->height();
    QRect erect = QRect(this->pos(), this->size());
    if (erect.top() < 0 || erect.left() < 0 | erect.right()>screenwidth /*| erect.bottom()>screenhight*/)
    {
        is_hiding = true;
        hideWidget();//此函数为前面动画的逆向动画效果；
    }
    else
    { 
        return;
    }
}

void autoHideWidget::mouseMoveEvent(QMouseEvent *event)
{
    // 只响应左键
    if (event->buttons() & Qt::LeftButton)
    {
        if (m_dragging)
        {
            // delta 相对偏移量,
            QPoint delta = event->globalPos() - m_startPosition;

            // 新位置：窗体原始位置  + 偏移量
            move(m_framePosition + delta);
        }
        /*QWidget::mouseMoveEvent(event);*/
    }
}

void autoHideWidget::mousePressEvent(QMouseEvent *event)
{
    // 只响应左键
    if (event->button() == Qt::LeftButton)
    {
        QRect titleRect = rect();
        /*titleRect.setBottom(titleRect.top() + 30);*/

        if (titleRect.contains(event->pos()))
        {
            m_dragging = true;
            m_startPosition = event->globalPos();
            m_framePosition = frameGeometry().topLeft();
        }
    }
}

void autoHideWidget::mouseRleaseEvent(QMouseEvent *event)
{
    m_dragging = false;
}

//窗体隐藏
void autoHideWidget::hideWidget()
{
    int screenwidth = QApplication::desktop()->width();
    int screenhight = QApplication::desktop()->height();
    QRect erect = QRect(this->pos(), this->size());
    QPropertyAnimation*animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setStartValue(erect);
    QRect enrect;
    if (erect.top() < 0)
    {
        enrect =  QRect(this->x(), -this->height() + 2, this->size().width(), this->rect().height());

    }
    if (erect.left() < 0)
    {
        enrect = QRect(-this->width() + 2, this->y(), this->size().width(), this->rect().height());
    }
    if (erect.right() > screenwidth)
    {
        enrect = QRect(screenwidth-2, this->y(), this->size().width(), this->rect().height());
    }
// 	if (erect.bottom() > screenhight)
// 	{
// 		enrect = QRect(this->x(), screenhight - 2, this->size().width(), this->rect().height());
// 	}
    animation->setEndValue(enrect);
    animation->start();
}

void autoHideWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())//如果拖动事件有资源定位器
    event->acceptProposedAction();//Accepts the drag event with the proposedAction；
}

void autoHideWidget::dropEvent(QDropEvent * event)
{
	if (event->mimeData()->hasUrls())
	{
        count++;//拖动文件数量+1;
		t= event->mimeData()->urls()[0];
		QFileInfo info(t.toLocalFile());
		QString path = info.absoluteFilePath();//将所拖动文件路径赋值给path;
        QString fileName=info.fileName();
		if (info.isSymLink())
		{
			path = info.symLinkTarget();//绝对路径赋值给path;
		}

        inputPath(path,fileName);

		QIcon icon = icon_provider.icon(path);//获取该路径下文件图标；

		if (count >= 1 && count < 9)//布局整体分为3列，每列8个，且已经计算好每个按钮所占大小和整个程序窗口大小相协调；
		{
			button = new buttonClicked(this);
			button->setAutoRaise(true);//按钮离开时。按钮恢复到弹起状态
			button->setIcon(icon);
			button->setIconSize(QSize(32, 32));
			button->setText(path);
			button->setToolButtonStyle(Qt::ToolButtonIconOnly);
			button->setGeometry(QRect(30, (count - 1) * 70 + 10, 40, 40));//参数为x,y,按钮矩形长和宽；
			button->show();
		}
		else if(count >= 9 && count < 17)
		{
			button = new buttonClicked(this);
			button->setAutoRaise(true);//按钮离开时。按钮恢复到弹起状态
			button->setIcon(icon);
			button->setIconSize(QSize(32, 32));
			button->setText(path);
			button->setToolButtonStyle(Qt::ToolButtonIconOnly);
			button->setGeometry(QRect(100, (count - 9) * 70 + 10, 40, 40));
			button->show();
		}
		else if (count >= 17 && count <= 24)
		{
			button = new buttonClicked(this);
			button->setAutoRaise(true);//按钮离开时。按钮恢复到弹起状态
			button->setIcon(icon);
			button->setIconSize(QSize(32, 32));
			button->setText(path);
			button->setToolButtonStyle(Qt::ToolButtonIconOnly);
			button->setGeometry(QRect(170, (count - 17) * 70 + 10, 40, 40));
			button->show();
		}
		else if(count > 24)
		{
			setAcceptDrops(false);//当拖进count>24时，不放进窗口；
		}

	}
	return;
}

autoHideWidget::~autoHideWidget()
{
    delete ui;
}

void autoHideWidget::reLoad()
{
    count = m_path.return_m_count();
    QVector <QString> path = m_path.return_array();
    for (int i = 0; i < count; i++)
    {
        QIcon icon = icon_provider.icon(path[i]);
        if (i>= 0 && i < 8)
        {
            button = new buttonClicked(this);
            button->setAutoRaise(true);//按钮离开时。按钮恢复到弹起状态
            //button->setStyleSheet("QtoolButton{background-color:black;border:4px solid gray;border-radius:10px;}");
            /*button->setAutoFillBackground(true);*/
            button->setStyleSheet(0);
            button->setIcon(icon);
            button->setIconSize(QSize(32, 32));
            button->setText(path[i]);
            button->setToolButtonStyle(Qt::ToolButtonIconOnly);
            button->setGeometry(QRect(30, (i) * 70 + 10, 40, 40));
            button->show();
        }
        else if (i >= 8 && i < 16)
        {
            button = new buttonClicked(this);
            button->setAutoRaise(true);//按钮离开时。按钮恢复到弹起状态
            button->setIcon(icon);
            button->setIconSize(QSize(32, 32));
            button->setText(path[i]);
            button->setToolButtonStyle(Qt::ToolButtonIconOnly);
            button->setGeometry(QRect(100, (i-8) * 70 + 10, 40, 40));
            button->show();
        }
        else if (i >= 16 && i <= 23)
        {
            button = new buttonClicked(this);
            button->setIcon(icon);
            button->setIconSize(QSize(32, 32));
            button->setText(path[i]);
            button->setToolButtonStyle(Qt::ToolButtonIconOnly);
            button->setGeometry(QRect(170, (count - 16) * 70 + 10, 40, 40));
            button->show();
        }
    }
}

void autoHideWidget::inputPath(QString  &path,QString fileName)
{
    //对文件进行移动
    QDir dir;
    QString currentPath=dir.currentPath();
    currentPath+="/testDir";
    qDebug() << "当前路径=" << currentPath;
    bool ok = dir.mkpath(currentPath);
    qDebug() << "ok="<<ok;
    QString old_path=path;
    QString new_path=currentPath+"/"+fileName;
    bool x= QFile::rename(old_path,new_path); //A路径移动到B路径
    qDebug()<<x;
    //将文件的现存路径
    path=new_path;
    m_path.addInfor(new_path);
	m_path.save();
}
void autoHideWidget::on_btnClose_clicked()
{
	this->close();
}
