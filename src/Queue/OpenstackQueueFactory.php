<?php

namespace Drupal\openstack_queues\Queue;

use Drupal\Core\Config\ConfigFactoryInterface;
use OpenCloud\Rackspace;

class OpenstackQueueFactory {

  /**
   * @var Rackspace $connection
   */
  private $connection;
  /**
   * @var ConfigFactoryInterface $configFactory
   */
  private $configFactory;
  /**
   * @var array $config
   */
  private $config;

  public function __construct(ConfigFactoryInterface $configFactory) {
    $this->configFactory = $configFactory;
  }

  /**
   * @param string $name
   *   The name of the collection holding key and value pairs.
   *
   * @return OpenstackQueue
   */
  public function get($name) {
    $config = $this->configFactory->get('openstack_queues.settings');
    $this->config = ($config->get($name)) ? $config->get($name) : $config->get('default');
    $this->connection = new Rackspace($this->config['auth_url'], $this->config['credentials']);
    return new OpenstackQueue($name, $this->connection, $this->config);
  }

}