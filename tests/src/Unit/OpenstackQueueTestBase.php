<?php

namespace Drupal\Tests\openstack_queues\Unit;

use Drupal\Tests\UnitTestCase;
use Guzzle\Http\Message\Response;
use OpenCloud\Tests\MockSubscriber;
use Opencloud\Rackspace;

class OpenstackQueueTestBase extends UnitTestCase {

  /**
   * @var Rackspace $client
   */
  protected $client;

  protected function addMockSubscriber($response) {
    $subscriber = new MockSubscriber(array($response), true);
    $this->client->addSubscriber($subscriber);
  }

  protected function makeResponse($body = null, $status = 200) {
    return new Response($status, array('Content-Type' => 'application/json'), $body);
  }

}