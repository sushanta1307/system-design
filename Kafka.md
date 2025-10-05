### Installation 

```sh
[sushsena@phoenix802783 etc]$ java -version
java version "1.8.0_461"
Java(TM) SE Runtime Environment (build 1.8.0_461-b11)
Java HotSpot(TM) 64-Bit Server VM (build 25.461-b11, mixed mode)
```

```sh
[sushsena@phoenix802783 ~]$ wget https://downloads.apache.org/kafka/3.8.0/kafka_2.13-3.8.0.tgz
tar -xzf kafka_2.13-3.8.0.tgz
cd kafka_2.13-3.8.0
```

### Hello World!

#### Terminal 1 -- start zookeeper
```sh
bin/zookeeper-server-start.sh config/zookeeper.properties
```

#### Terminal 2 -- Start Kafka Broker
```sh
bin/kafka-server-start.sh config/server.properties
```

#### Terminal 3 -- Create a Topic and Test
```sh
[sushsena@phoenix802783 kafka_2.13-3.8.0]$ bin/kafka-topics.sh --create --topic test-topic --bootstrap-server localhost:9092 --partitions 1 --replication-factor 1
Created topic test-topic.

[sushsena@phoenix802783 kafka_2.13-3.8.0]$ bin/kafka-topics.sh --list --bootstrap-server localhost:9092
test-topic
```

#### Terminal 4 -- Producer
```sh
[sushsena@phoenix802783 kafka_2.13-3.8.0]$ bin/kafka-console-producer.sh --topic test-topic --bootstrap-server localhost:9092
>My Own Message
>Hii
>Hello
>
```

#### Terminal 5 -- Consumer
```sh
[sushsena@phoenix802783 kafka_2.13-3.8.0]$ bin/kafka-console-consumer.sh --topic test-topic --from-beginning --bootstrap-server localhost:9092
My Own Message
Hii
Hello
```

### Multiple Topics

#### Create topics
```sh
# Create orders topic
bin/kafka-topics.sh --create --topic orders --bootstrap-server localhost:9092 --partitions 1 --replication-factor 1

# Create payments topic
bin/kafka-topics.sh --create --topic payments --bootstrap-server localhost:9092 --partitions 1 --replication-factor 1

# Create shipments topic
bin/kafka-topics.sh --create --topic shipments --bootstrap-server localhost:9092 --partitions 1 --replication-factor 1
```

#### Start Producers
```sh
bin/kafka-console-producer.sh --topic orders --bootstrap-server localhost:9092
bin/kafka-console-producer.sh --topic payments --bootstrap-server localhost:9092
bin/kafka-console-producer.sh --topic shipments --bootstrap-server localhost:9092
```

#### Start Consumers
```
bin/kafka-console-consumer.sh --topic orders --from-beginning --bootstrap-server localhost:9092
bin/kafka-console-consumer.sh --topic payments --from-beginning --bootstrap-server localhost:9092
bin/kafka-console-consumer.sh --topic shipments --from-beginning --bootstrap-server localhost:9092
```

### Partitioning

#### Create a topic with mulitple partitions
```sh
bin/kafka-topics.sh --create --topic orders-partitioned --bootstrap-server localhost:9092 --partitions 3 --replication-factor 1

# Verify
bin/kafka-topics.sh --describe --topic orders-partitioned --bootstrap-server localhost:9092

# Delete a Topic
bin/kafka-topics.sh --delete --topic orders --bootstrap-server localhost:9092
```

#### Start the Producer with Key
```sh
bin/kafka-console-producer.sh --topic orders-partitioned --bootstrap-server localhost:9092 --property "parse.key=true" --property "key.separator=:"
>key1:Order-101
>key2:Order-102
>key3:Order-103
>key1:Order-104
```

#### Start mulitple Consumers with same group
```sh
bin/kafka-console-consumer.sh --topic orders-partitioned --group order-group --bootstrap-server localhost:9092

# Verify
bin/kafka-consumer-groups.sh --bootstrap-server localhost:9092 --describe --group order-group
```
