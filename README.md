# Задача многопроцессорного планирования

[![Build Status](https://www.travis-ci.com/2ToThe10th/MultiprocessorSchedulingProblem.svg?branch=master)](https://www.travis-ci.com/2ToThe10th/MultiprocessorSchedulingProblem)

[Задача об оптимальном расписании в overleaf](https://ru.overleaf.com/read/gbtkvwnmtgjt)

В проекте рассмотрена задача об оптимальном расписании, когда производительность всех машин одинакова. Так же данная
задача называется задачей многопроцессорного планирования. Доказана __NP__-полнота, построен эвристический алгоритм и
показано что он дает 1.33-приближение

Для запуска тестов воспользуйтесь командами:

```
cmake
make
./MultiprocessorSchedulingProblem
```

Так же результаты тестов можно посмотреть
на [travis ci](https://www.travis-ci.com/github/2ToThe10th/MultiprocessorSchedulingProblem)