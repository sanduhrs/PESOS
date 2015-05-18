<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Create a Amazon App
 * @see https://sellercentral.amazon.com/gp/homepage.html
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'Amazon',
  'class' => 'AmazonSilo',
);

/**
 * Class AmazonSilo.
 */
class AmazonSilo extends Silo {

  protected $title = 'Amazon';

  protected $scopes = array('profile');

  public function connect() {
    parent::connect();

    try {
      $this->token = $this->storage->retrieveAccessToken($this->title);
    }
    catch (Exception $e) {
      if (!empty($_GET['code'])) {
        // This was a callback request from remote, get the token.
        $this->service->requestAccessToken($_GET['code']);
      }
      else {
        $url = $this->service->getAuthorizationUri();
        header('Location: ' . $url);
      }
    }
  }

}
