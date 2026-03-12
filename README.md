# 课程选课系统 (Course Selection System) v1.9

> 逻辑程序基本实现 —— 新增 PostgreSQL 数据库持久化存储  
> v1.1 新增：账号密码登录功能  
> v1.5 新增：数据库读取表存储功能  
> v1.9 新增：数据库持久化存储

---

## 📋 项目简介
课程选课系统是一个基于 C++ 开发的控制台应用程序，实现了学生选课、教师评分等核心功能。系统采用面向对象设计，通过 User 基类派生出 Student 和 Teacher 类，实现了不同角色的权限管理。

**v1.9 重磅更新**：集成 PostgreSQL 数据库，实现数据持久化存储，程序重启后数据不丢失！

---

## ✨ 功能特性

### 🔐 通用功能
| 功能 | 描述 |
|:----|:-----|
| 👤 身份选择 | 启动后选择学生/教师身份 |
| 🔑 账号登录 | 输入账号密码进行身份验证 |
| 💾 数据持久化 | 程序自动保存数据到 PostgreSQL |
| 🚪 安全退出 | 正常退出当前用户会话 |

### 👨‍🎓 学生功能
| 功能 | 描述 |
|:----|:-----|
| 📚 查看可选课程 | 浏览所有可选的课程列表 |
| ✅ 选课 | 选择感兴趣的课程 |
| ❌ 退选课程 | 取消已选择的课程 |
| 📊 查看成绩 | 查看自己所有已选课程的成绩 |

### 👨‍🏫 教师功能
| 功能 | 描述 |
|:----|:-----|
| 📖 查看授课课程 | 浏览自己教授的课程列表 |
| ✏️ 成绩打分 | 为选课学生打分（1-100分） |
| 📈 查看学生成绩 | 查看自己所教课程的学生成绩 |

---

## 🗄️ 数据库设计

### 数据表结构
| 表名 | 字段 | 说明 |
|:----|:-----|:-----|
| **course** | id, name | 课程表 |
| **student** | id, name, account, password | 学生表 |
| **teacher** | id, name, account, password | 教师表 |
| **studentcourse** | sid, cid, grades | 学生选课及成绩表 |
| **teachercourse** | tid, cid | 教师授课表 |

### 表命名规则
所有表名格式：`表名 + 学号` (如 `course20240511604041`)

---

## 🏗️ 系统架构

### 核心类设计

### 数据持久化流程

#### 程序启动 (`initialize()`)
1. 初始化 PostgreSQL 连接
2. 检查并创建必要的数据表
3. 从数据库加载数据：
   - 加载 `course`、`student`、`teacher` 表到对象容器
   - 加载 `studentcourse` 表，恢复选课关系和成绩（grades 为 -1 表示未打分）
   - 加载 `teachercourse` 表，恢复教师授课关系

#### 程序退出 (`saveEndIntoSql()`)
- 保存 `studentcourse` 表数据（选课关系及成绩）
- 成绩为 -1 表示未打分

---

## 🚀 快速开始

### 环境要求
- C++17 或更高版本
- PostgreSQL 12+
- libpqxx 开发库
- CMake 3.10+

### 编译安装
```bash
# 克隆仓库
git clone https://github.com/firefly-live/teachingLoginSystem.git
cd teachingLoginSystem

# 创建构建目录
mkdir build && cd build

# 配置CMake
cmake ..

# 编译
make

# 运行
./LoginSystem
