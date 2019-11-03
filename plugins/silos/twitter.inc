<?php
/**
 * @file
 * Silo implementation as ctools plugin.
 *
 * Create a Twitter App
 * @see https://apps.twitter.com/
 */

// Ctools plugin definition.
$plugin = array(
  'title' => 'Twitter',
  'class' => 'TwitterSilo',
);

/**
 * Class TwitterSilo.
 */
class TwitterSilo extends Silo {

  protected $title = 'Twitter';

  public function authenticate() {
    parent::authenticate();

    try {
      $this->token = $this->storage->retrieveAccessToken($this->title);
    }
    catch(Exception $e) {
      if (!empty($_GET['oauth_token'])) {
        $this->token = $this->storage->retrieveAccessToken('Twitter');

        // This was a callback request from twitter, get the token
        $this->service->requestAccessToken(
          $_GET['oauth_token'],
          $_GET['oauth_verifier'],
          $this->token->getRequestTokenSecret()
        );

        // Send a request now that we have access token
        $result = json_decode($twitterService->request('account/verify_credentials.json'));
      }
      else {
        // extra request needed for oauth1 to request a request token :-)
        $this->token = $this->service->requestRequestToken();

        $url = $this->service->getAuthorizationUri(array('oauth_token' => $this->token->getRequestToken()));
        header('Location: ' . $url);
      }
    }
  }

  public function getItems() {
    return json_decode(
      $this->service->request('statuses/user_timeline.json?count=25')
    );
  }

}

