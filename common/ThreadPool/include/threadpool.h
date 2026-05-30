#ifndef COMMON_THREADPOOL_H_
#define COMMON_THREADPOOL_H_

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

#include "interfaces/IThreadPool.h"

/**
 * @brief Реалізація пулу потоків для асинхронного виконання завдань.
 *
 * Клас створює фіксовану кількість робочих потоків під час ініціалізації
 * та повторно використовує їх для виконання завдань, що надходять у чергу.
 * Такий підхід дозволяє уникнути накладних витрат на постійне створення
 * та знищення потоків, підвищуючи продуктивність багатопотокових застосунків.
 *
 * ThreadPool є реалізацією інтерфейсу IThreadPool та забезпечує
 * потокобезпечне додавання завдань і очікування завершення їх виконання.
 */
class ThreadPool : public IThreadPool {
public:
    /**
   * @brief Створює пул потоків.
   *
   * Ініціалізує вказану кількість робочих потоків, які очікують
   * на надходження завдань у внутрішній черзі.
   *
   * @param num_threads Кількість потоків у пулі.
   * За замовчуванням використовується кількість апаратних потоків,
   * доступних на поточній системі.
   */
    explicit ThreadPool(size_t num_threads = std::thread::hardware_concurrency());

    /**
   * @brief Знищує пул потоків.
   *
   * Зупиняє всі робочі потоки та коректно звільняє використані ресурси.
   * Перед завершенням очікує завершення виконання активних завдань.
   */
    ~ThreadPool() override;

    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;

    /**
   * @brief Очікує завершення всіх завдань у пулі.
   *
   * Блокує поточний потік до моменту, коли черга завдань стане порожньою
   * та всі активні завдання завершать виконання.
   */
    void waitAll();

private:
    /**
   * @brief Додає нове завдання до черги виконання.
   *
   * Завдання буде виконано одним із доступних робочих потоків.
   *
   * @param task Функціональний об'єкт, який необхідно виконати.
   */
    void enqueueTask(std::function<void()> task) override;

    /**
   * @brief Контейнери робочих потоків пулу.
   */
    std::vector<std::thread> workers_;

    /**
   * @brief Черга завдань, що очікують виконання.
   */
    std::queue<std::function<void()>> tasks_;

    /**
   * @brief М'ютекс для синхронізації доступу до черги завдань.
   */
    std::mutex queue_mutex_;

    /**
   * @brief Умова для сповіщення потоків про появу нових завдань.
   */
    std::condition_variable condition_;

    /**
   * @brief Умова для сповіщення про завершення всіх активних завдань.
   */
    std::condition_variable done_condition_;

    /**
   * @brief Прапорець завершення роботи пулу потоків.
   */
    bool stop_{false};

    /**
   * @brief Кількість завдань, що наразі виконуються.
   */
    size_t active_tasks_ = 0;
};

#endif  // COMMON_THREADPOOL_H_
