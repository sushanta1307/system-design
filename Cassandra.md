### Installation

### Commands

#### Start Cassandra
```sh
export JAVA_HOME=/usr/lib/jvm/java-11-openjdk-11.0.25.0.9-7.0.1.el9.x86_64

cassandra -f
```

#### Hello World!
```sql
[sushsena@phoenix802783 cassandra]$ cqlsh
Connected to Test Cluster at 127.0.0.1:9042
[cqlsh 6.1.0 | Cassandra 4.1.5 | CQL spec 3.4.6 | Native protocol v5]
Use HELP for help.
cqlsh> CREATE KEYSPACE testks WITH replication = {'class': 'SimpleStrategy', 'replication_factor': 1};
cqlsh> USE testks;
cqlsh:testks> CREATE TABLE users (
          ...    id UUID PRIMARY KEY,
          ...    name text,
          ...    age int
          ... );

-- Insert
cqlsh:testks> INSERT INTO users (id, name, age) VALUES (uuid(), 'Sushanta', 26);
cqlsh:testks> SELECT * FROM users;

 id                                   | age | name
--------------------------------------+-----+----------
 3b57dc8c-3b48-4a7b-96ee-8572ef166880 |  26 | Sushanta

(1 rows)

-- Update
cqlsh:testks> UPDATE users SET name='Rahul' WHERE id=c6338311-ca47-4106-88be-103ea70ea922;

-- Delete a row
cqlsh:testks> DELETE FROM users
          ... WHERE id  = c6338311-ca47-4106-88be-103ea70ea922;

-- Delete a column
cqlsh:testks> DELETE age from users where id = ebea2f6d-5360-485f-90dd-2308fb0d7f9d;

-- Scope out current Keyspace
cqlsh:testks> use SYSTEM;
cqlsh:system> describe tables

-- Partitioning and Clustering
CREATE TABLE orders (
    customer_id UUID,
    order_date TIMESTAMP,
    order_id UUID,
    amount DECIMAL,
    PRIMARY KEY (customer_id, order_date, order_id)
) WITH CLUSTERING ORDER BY (order_date DESC);

-- Secondary indexing
cqlsh:shop> CREATE INDEX shopKeeper_idx on orders (shopkeepr_id);
cqlsh:shop> select * from orders where shopkeepr_id = 551e3547-66f0-4d76-91ac-d2e4c8471f7c;

 customer_id                          | order_date                      | order_id                             | amount | shopkeepr_id
--------------------------------------+---------------------------------+--------------------------------------+--------+--------------------------------------
 06c957a0-d502-48c5-a38d-0e4557594bf0 | 2025-10-08 06:46:23.632000+0000 | cdbdae14-6e60-4905-ba57-511405ec5f7d |   null | 551e3547-66f0-4d76-91ac-d2e4c8471f7c

(1 rows)

-- Materialized View
cqlsh:shop> CREATE MATERIALIZED VIEW shopkeeper AS SELECT * FROM orders WHERE shopkeepr_id IS NOT NULL AND customer_id IS NOT NULL AND order_date IS NOT NULL AND order_id IS NOT NULL PRIMARY KEY (shopkeepr_id, customer_id, order_date, order_id);

cqlsh:shop> select * from shopkeeper where shopkeepr_id = 551e3547-66f0-4d76-91ac-d2e4c8471f7c;

 shopkeepr_id                         | customer_id                          | order_date                      | order_id                             | amount
--------------------------------------+--------------------------------------+---------------------------------+--------------------------------------+--------
 551e3547-66f0-4d76-91ac-d2e4c8471f7c | 06c957a0-d502-48c5-a38d-0e4557594bf0 | 2025-10-08 06:46:23.632000+0000 | cdbdae14-6e60-4905-ba57-511405ec5f7d |   null

(1 rows)
```

#### Hands-On: Multi-Node Cassandra on a Single VM
- Prepare Directories for Each Node
- Copy and Edit `cassandra.yaml` for Each Node
- Start Each Node
