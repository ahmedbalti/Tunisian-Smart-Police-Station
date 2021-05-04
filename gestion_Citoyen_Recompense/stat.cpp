#include "stat.h"
#include "ui_stat.h"
#include <qvariant.h>
#include "recompense.h"
#include <QGridLayout>
#include <QWidget>
#include <QtCore>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLegend>
#include <QtCharts/QLineSeries>
#include <ui_stat.h>
#include <qwindow.h>
statistiques::statistiques(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistiques)
{
    //  ui->setupUi(this) ;

      QBarSet *set0 = new QBarSet("ticket cinéma");
      QBarSet *set1 = new QBarSet("Bande d'achat");
      QBarSet *set2 = new QBarSet("resto");



      *set0 <<  c.calculer("cinema")<< 0 << 0;
      *set1 << 0 << c.calculer("bande d'achat") << 0;
      *set2 << 0 << 0 << c.calculer("resto");

      QBarSeries *series = new QBarSeries();
      series->append(set0);
      series->append(set1);
      series->append(set2);

      QChart *chart = new QChart();
      chart->addSeries(series);
      chart->setTitle("Statistique des récompenses");
      chart->setAnimationOptions(QChart::SeriesAnimations);

      QStringList categories;
      categories << "ticket cinéma"
                 << "Bande d'achat"
                 << "resto";

      QBarCategoryAxis *axis = new QBarCategoryAxis();
      axis->append(categories);
      chart->createDefaultAxes();
      chart->setAxisX(axis, series);

      chart->legend()->setVisible(true);
      chart->legend()->setAlignment(Qt::AlignBottom);

      QChartView *chartview = new QChartView(chart);
      chartview->setRenderHint(QPainter::Antialiasing);
      QGridLayout *mainLayout = new QGridLayout;
      mainLayout->addWidget(chartview, 1, 1);
      setLayout(mainLayout);
      setMinimumSize(800, 600);
}
statistiques ::~statistiques()
{
delete ui;
}

