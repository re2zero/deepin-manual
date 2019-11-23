/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DEEPIN_MANUAL_VIEW_WEB_WINDOW_H
#define DEEPIN_MANUAL_VIEW_WEB_WINDOW_H

#include "controller/search_result.h"
#include "widget/manual_webview.h"

#include <QTimer>
#include <QtDBus/QtDBus>

#include <DMainWindow>
#include <DButtonBox>

namespace dman {

class I18nProxy;
class ImageViewer;
class ImageViewerProxy;
class ManualProxy;
class SearchCompletionWindow;
class SearchManager;
class SearchProxy;
class ThemeProxy;
class TitleBar;
class TitleBarProxy;
class SearchEdit;
class DButtonBox;

class WebWindow : public Dtk::Widget::DMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QString appName READ appName WRITE setAppName)

public:
    explicit WebWindow(SearchManager *search_manager, QWidget *parent = nullptr);
    ~WebWindow() override;

    // Get app name of manual currently presented.
    const QString &appName() const
    {
        return app_name_;
    }

    bool eventFilter(QObject *watched, QEvent *event) override;

    static void showAllShortcut();

    Dtk::Widget::DButtonBoxButton *m_backButton;
    Dtk::Widget::DButtonBoxButton *m_forwardButton;

signals:
    void closed(const QString &app_name);

public slots:
    void setAppName(const QString &app_name);
    void slot_ButtonHide();
    void slot_ButtonShow();

protected:
    void closeEvent(QCloseEvent *event) override;

    // Update width of title bar when main window is resized.
    void resizeEvent(QResizeEvent *event) override;

private:
    void initConnections();
    void initUI();
    void initShortcuts();
    void initDBus();

    QString app_name_;
    SearchManager *search_manager_ = nullptr;
    SearchProxy *search_proxy_ = nullptr;
    ThemeProxy *theme_proxy_ = nullptr;
    SearchCompletionWindow *completion_window_ = nullptr;
    I18nProxy *i18n_ = nullptr;
    ImageViewer *image_viewer_ = nullptr;
    ImageViewerProxy *image_viewer_proxy_ = nullptr;
    ManualProxy *manual_proxy_ = nullptr;
    TitleBar *title_bar_ = nullptr;
    TitleBarProxy *title_bar_proxy_ = nullptr;
    ManualWebView *web_view_ = nullptr;
    QTimer search_timer_;
    Dtk::Widget::DButtonBox *buttonBox;
    SearchEdit *search_edit_;
    QPoint start_point_;
    int start_drag_x;

private slots:
    void onSearchEditFocusOut();
    void onSearchButtonClicked();
    void onSearchContentByKeyword(const QString &keyword);
    void onSearchResultClicked(const SearchAnchorResult &result);
    void onSearchAnchorResult(const QString &keyword,
                              const SearchAnchorResultList &result);
    void onSearchTextChanged(const QString &text);
    void onSearchTextChangedDelay();
    void onTitleBarEntered();
    void onWebPageLoadFinished(bool ok);

    void Slot_ManualSearchByKeyword(const QString &data);
};

}  // namespace dman

#endif  // DEEPIN_MANUAL_VIEW_WEB_WINDOW_H
