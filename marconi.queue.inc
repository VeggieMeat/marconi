<?php

/**
 * @file
 * Contains MarconiQueue class implementing DrupalQueueInterface
 */

class MarconiQueue implements DrupalQueueInterface {

  /**
   * Start working with a queue.
   *
   * @param string name
   *   The name of the queue to work with.
   */

  public function __construct($name) {
    if (marconi_loaded()) {
      $this->name = $name;
      $this->params = marconi_get_queue_options($name);
      $this->connect();
    }
  }

  /**
   * Create a queue.
   *
   * @param string $name
   *   The name of the queue to create.
   */
  public function createQueue($name) {
    $this->queue = $this->service->getQueue();
    $this->queue->create(
      array(
        'name' => $name,
        'metadata' => $this->params['metadata'],
      )
    );
  }

  /**
   * Delete a queue.
   *
   * @param string $name
   *   The name of the queue to delete.
   */
  public function deleteQueue($name) {
    $this->queue = $this->service->getQueue();
    $this->queue->setName($name);
    $this->queue->delete();
  }

  /**
   * Add a queue item and store it directly to the queue.
   *
   * @param object $data
   *   Arbitrary data to be associated with the new task in the queue.
   *
   * @return bool
   */
  public function createItem($data) {
    $message = $this->queue->getMessage();
    $message->setBody(json_encode($data));
    $message->setTtl($this->params['ttl']);
    return $message->create();
  }

  /**
   * Claim an item in the queue for processing.
   *
   * @param int $ttl
   *   How long the processing is expected to take, in seconds. Value must be
   *   between 60 and 43200 seconds. The default is 12 hours.
   * @param int $grace
   *   The message grace period. The server extends the lifetime of claimed
   *   messages at least as long as the claim itself, plus a specified grace
   *   period to deal with crashed workers. Value must be between 60 and 43200
   *   seconds. Default is 12 hours.
   */
  public function claimItem($ttl = 43200, $grace = 43200) {
    $options = array();
    $options['ttl'] = $ttl;
    $options['grace'] = $grace;

    // Drupal claims items one at a time.
    $options['limit'] = 1;

    $message = $this->queue->claimMessages($options);

    $item->item_id = $message->getId();
    $item->data = json_decode($message->getBody());

    if (!empty($item->item_id)) {
      return $item;
    }

    return FALSE;
  }

  /**
   * Deletes an item from the queue.
   *
   * @param Message $item
   *   The item to be deleted.
   */
  public function deleteItem($item) {
    $this->queue->deleteMessages(array($item->item_id));
  }

  /**
   * Connect to a Marconi queue.
   */
  protected function connect() {
    $params = $this->params;
    $class = 'OpenCloud\\' . $params['provider'];
    if (!class_exists($class)) {
      $class = 'OpenCloud\OpenStack';
    }
    $this->connection = new $class($params['auth_url'], $params['credentials']);
    $this->service = new OpenCloud\Queues\Service($this->connection, $params['service'], $params['region']);
    $this->service->setClientId($params['client_id']);
  }
}
