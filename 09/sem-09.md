#  ДЗ №8
## Markdown report <br>

### 1. Ганина Ксения Андреевна (тг для вопросов: @kgnn47) <br>
### 2. БПИ212 <br>

![image](https://user-images.githubusercontent.com/114473740/229345432-8c07ee06-f50a-4a22-ad89-65c42f6de3a6.png)

________________________

### 3. Изменения в коде. <br>

#### 3.1 common.h

Для реализации кольцевого буфера используем два указателя: указатель на начало и конец буфера

```с

typedef struct {
    int have_reader;      // индикатор наличия читателя
    int reader_pid;       // идентификатор процесса читателя
    int have_writer;      // индикатор наличия писателя
    int writer_pid;       // идентификатор процесса писателя

    int data[BUF_SIZE];
    int start;		// указатель 1 (для читателя)
    int end;		// указатель 2 (для писателя)
} buffer_t;

```

#### 3.2 common.c

При записи данных в буфер указатель на конец буфера будет сдвигаться на одну позицию вперед. Если указатель на конец буфера достиг конца буфера, он будет перемещен в начало буфера (это реализовано через % BUF_SIZE). Аналогично для читателя, только там смещается указатель на начало буфера. При инициализации буфера оба указателя равны нулю

```с

void buffer_init(buffer_t *buffer) {
    buffer->start = 0;
    buffer->end = 0;
}

void buffer_write(buffer_t *buffer, int data) {

    buffer->data[buffer->end] = data;
    buffer->end = (buffer->end + 1) % BUF_SIZE;
}

int buffer_read(buffer_t *buffer) {

    int data = buffer->data[buffer->start];
    buffer->start = (buffer->start + 1) % BUF_SIZE;

    return data;
}

```

#### 3.3 reader.c

Заменяем буфер на новую структуру:

```с
//получить доступ к памяти
buffer = mmap(0, sizeof (buffer_t), PROT_WRITE|PROT_READ, MAP_SHARED, buf_id, 0);
if (buffer == (buffer_t*)-1 ) {
  perror("writer: mmap");
  exit(-1);
}
printf("mmap checkout\n");

buffer_init(buffer);

printf("buffer got access\n");

```

Внутри алгоритма читателя меняем получение индекса (получаем по первому указателю) и запускаем функцию чтения из буфера:

```с

// начать чтение из буфера

int i = buffer->start;

printf("current i = %d\n", i);

int result = buffer_read(buffer);

```

#### 3.4 writer.c

Заменяем буфер на новую структуру:

```с

//получить доступ к памяти
buffer = mmap(0, sizeof (buffer_t), PROT_WRITE|PROT_READ, MAP_SHARED, buf_id, 0);
if (buffer == (buffer_t*)-1 ) {
  perror("writer: mmap");
  exit(-1);
}
printf("mmap checkout\n");

buffer_init(buffer);

printf("buffer initialized\n");

```
Внутри алгоритма писателя меняем получение индекса (получаем по второму указателю) и запускаем функцию записи в буфер:

```с

// начать запись данных в буфер
int i = buffer->end;
printf("current i = %d\n", i);
int data = rand() % 11;
buffer_write(buffer, data);

```

________________________

### 4. Примеры вывода. <br>

Virtual Ubuntu <br>

Сначала запуск writer, потом reader:
![image](https://user-images.githubusercontent.com/114473740/229367274-d9311a42-6f74-4407-aaec-2f1d18c40c51.png)

Сначала запуск reader, потом writer:
![image](https://user-images.githubusercontent.com/114473740/229367344-0da67dd7-2d9c-4422-a65d-3575669ee7e8.png)

Можно закомментировать ```buffer_init(buffer);``` (см. 3.3) у читателя, чтобы писатель не начинал запись заново:
![image](https://user-images.githubusercontent.com/114473740/229367804-f21caa63-83e0-4192-81a4-8d2cc0820d1d.png)
